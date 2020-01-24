#pragma once

#define FQN_DNSPROXY "com/adguard/dnslibs/proxy/DnsProxy"
#define FQN_DNSPROXY_SETTINGS "com/adguard/dnslibs/proxy/DnsProxySettings"
#define FQN_BLOCKING_MODE FQN_DNSPROXY_SETTINGS "$BlockingMode"
#define FQN_UPSTREAM_SETTINGS "com/adguard/dnslibs/proxy/UpstreamSettings"
#define FQN_LISTENER_SETTINGS "com/adguard/dnslibs/proxy/ListenerSettings"
#define FQN_LISTENER_PROTOCOL FQN_LISTENER_SETTINGS "$Protocol"
#define FQN_DNS64_SETTINGS "com/adguard/dnslibs/proxy/Dns64Settings"
#define FQN_DNSPROXY_EVENTS "com/adguard/dnslibs/proxy/DnsProxy$EventsAdapter"
#define FQN_REQ_PROC_EVENT "com/adguard/dnslibs/proxy/DnsRequestProcessedEvent"
#define FQN_CERT_VERIFY_EVENT "com/adguard/dnslibs/proxy/CertificateVerificationEvent"
#define FQN_DNSSTAMP "com/adguard/dnslibs/proxy/DnsStamp"
#define FQN_DNSSTAMP_PROTOTYPE FQN_DNSSTAMP "$ProtoType"
