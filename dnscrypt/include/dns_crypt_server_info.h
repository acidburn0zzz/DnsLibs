#pragma once

#include <chrono>
#include <cstdint>
#include <string>
#include <utility>
#include <functional>
#include "common/defs.h"
#include <dns_crypt_utils.h>
#include <ag_socket.h>

namespace ag::dnscrypt {

/**
 * Cert info contains DnsCrypt server certificate data retrieved from the server
 */
struct cert_info {
    uint32_t serial; /** Cert serial number (the cert can be superseded by another one with a higher serial number) */
    key_array server_pk; /** Server public key */
    key_array shared_key; /** Shared key */
    client_magic_array magic_query;
    crypto_construction encryption_algorithm; /** Encryption algorithm */
    uint32_t not_before; /** Cert is valid starting from this date (epoch time) */
    uint32_t not_after; /** Cert is valid until this date (epoch time) */
};

/**
 * Server info contains DNSCrypt server information necessary for decryption/encryption
 */
struct server_info {
    struct fetch_result {
        cert_info certificate;
        std::chrono::milliseconds round_trip_time;
        ErrString error;
    };

    struct encrypt_result {
        Uint8Vector ciphertext;
        Uint8Vector client_nonce;
        ErrString error;
    };

    struct decrypt_result {
        Uint8Vector message;
        ErrString error;
    };

    /**
     * Fetch DNSCrypt certificate using server info
     * @param timeout Timeout for read/write operations (0 means infinite timeout)
     * @param socket_factory Socket factory which creates sockets for data exchange
     * @param socket_parameters Connection socket parameters
     * @return Fetch result
     */
    fetch_result fetch_current_dnscrypt_cert(std::chrono::milliseconds timeout,
            const socket_factory *socket_factory, socket_factory::socket_parameters socket_parameters);

    /**
     * Encrypt packet using server info
     * @param protocol Protocol
     * @param packet Packet to encrypt
     * @return Encryption result
     */
    encrypt_result encrypt(utils::TransportProtocol protocol, Uint8View packet) const;

    /**
     * @brief Decrypt packet using server info
     * @param proto Protocol
     * @param packet Packet to decrypt
     * @return Decryption result
     */
    decrypt_result decrypt(Uint8View encrypted, Uint8View nonce) const;

    template<typename T>
    void set_server_address(T&& value) { m_server_address = std::forward<T>(value); }

    decltype(auto) get_provider_name() const { return m_provider_name; }

    decltype(auto) get_server_cert() const { return m_server_cert; }

private:
    struct txt_to_cert_info_result {
        cert_info certificate;
        ErrString error;
    };

    txt_to_cert_info_result txt_to_cert_info(const ldns_rr &answer_rr) const;

    key_array m_secret_key; /** Client secret key */
    key_array m_public_key; /** Client public key */
    Uint8Vector m_server_public_key; /** Server public key */
    std::string m_server_address; /** Server IP address */
    std::string m_provider_name; /** Provider name */
    cert_info m_server_cert; /** Certificate info (obtained with the first unencrypted DNS request) */

    friend class client;
};

} // namespace ag::dnscrypt
