#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>
#include "common/defs.h"
#include "common/net_utils.h"
#include <ldns/ldns.h>

namespace ag::dnscrypt {

constexpr size_t MAX_DNS_UDP_SAFE_PACKET_SIZE = 1252;
constexpr size_t CLIENT_MAGIC_LEN = 8;
constexpr size_t KEY_SIZE = 32;
constexpr uint16_t DEFAULT_PORT = 443;

using key_array = Uint8Array<KEY_SIZE>;
using client_magic_array = Uint8Array<CLIENT_MAGIC_LEN>;

using ldns_pkt_ptr = UniquePtr<ldns_pkt, &ldns_pkt_free>;
using ldns_buffer_ptr = UniquePtr<ldns_buffer, &ldns_buffer_free>;

/**
 * Crypto construction represents the encryption algorithm
 */
enum class crypto_construction : uint16_t {
    UNDEFINED, /** UNDEFINED is the default value for empty cert_info only */
    X_SALSA_20_POLY_1305 = 0x0001, /** X_SALSA_20_POLY_1305 encryption */
    X_CHACHA_20_POLY_1305 = 0x0002, /** X_CHACHA_20_POLY_1305 encryption */
};

/**
 * Convert crypto construction to string view
 * @param value Crypto construction to convert
 * @return String representation if value holds valid crypto construction, string view with empty string otherwise
 */
std::string_view crypto_construction_str(crypto_construction value);

} // namespace ag::dnscrypt
