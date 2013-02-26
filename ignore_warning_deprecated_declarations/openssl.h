#ifndef OPENSSL_H
#define OPENSSL_H

#ifdef __APPLE__

#define SSL_CTX_free(ctx)                                             \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_CTX_free((ctx))                                               \
    _Pragma("clang diagnostic pop")

#define SSL_shutdown(ctx)                                             \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_shutdown((ctx))                                               \
    _Pragma("clang diagnostic pop")

#define SSL_free(ctx)                                                 \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_shutdown((ctx))                                               \
    _Pragma("clang diagnostic pop")

#define SSL_load_error_strings()                                      \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_load_error_strings()                                          \
    _Pragma("clang diagnostic pop")

#define SSL_load_error_strings()                                      \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_load_error_strings()                                          \
    _Pragma("clang diagnostic pop")

#define SSL_library_init()                                            \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_library_init()                                                \
    _Pragma("clang diagnostic pop")

#define SSL_CTX_new(method)                                           \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_CTX_new((method))                                             \
    _Pragma("clang diagnostic pop")

#define SSL_CTX_use_certificate_chain_file(ctx, path)                 \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_CTX_use_certificate_chain_file((ctx), (path))                 \
    _Pragma("clang diagnostic pop")

#define SSL_CTX_use_PrivateKey_file(ctx, path, filetype)              \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_CTX_use_PrivateKey_file((ctx), (path), (filetype))            \
    _Pragma("clang diagnostic pop")

#define SSL_new(ctx)                                                  \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_new((ctx))                                                    \
    _Pragma("clang diagnostic pop")

#define SSL_set_fd(ctx, fd)                                           \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_set_fd((ctx), (fd))                                           \
    _Pragma("clang diagnostic pop")

#define SSL_connect(ssl)                                              \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_connect((ssl))                                                \
    _Pragma("clang diagnostic pop")

#define ERR_print_errors_fp(fd)                                       \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    ERR_print_errors_fp((fd))                                         \
    _Pragma("clang diagnostic pop")

#define SSL_get_error(ssl, r)                                         \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_get_error((ssl), (r))                                         \
    _Pragma("clang diagnostic pop")

#define SSL_write(ssl, buf, len)                                      \
    _Pragma("clang diagnostic push")                                  \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"") \
    SSL_write((ssl), (buf), (len))                                    \
    _Pragma("clang diagnostic pop")

#endif    /* __APPLE__ */

#endif
