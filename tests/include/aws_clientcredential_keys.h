/*
 * Amazon FreeRTOS V201906.00 Major
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

/*
 * @brief PEM-encoded client certificate.
 *
 * @todo If you are running one of the Amazon FreeRTOS demo projects, set this
 * to the certificate that will be used for TLS client authentication.
 *
 * @note Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWTCCAkGgAwIBAgIUVrqx9d/728Z8QTl8STS/5pCODKwwDQYJKoZIhvcNAQEL\n"\
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n"\
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE5MDIyMTIzNTUx\n"\
"MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n"\
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAK5E8M9LIipNEOez+9zr\n"\
"m7KjV4BHwDA7/1Kh2xcuXwdaedEIqF4Rpo1ZL+WIRgYKWj3QZxj1Nmld3FbbvIPJ\n"\
"/p8mrWNyT3NuHKhx6KCYQmeMo/R5gEkb2DomHiF/gtU/B1CysMhUqFUQkYLT2QyR\n"\
"c/1VUeAnDmkOxqHNLrfbYQbhI0N7o4HFK22NmAZsrTGX/Ve486DCUcMIpyapeABz\n"\
"GZUbHJwsOKwNHCevyeqwl7wb4iqW+OXpGHsLxWykhpAtt/dZAj+pU5zHO0y/FQxT\n"\
"haemSi3FhO97YUA5qMIfUZZDHvozYsVtDkZnBq0r3ipiu7iJYmn5cO/HIgmHjgXa\n"\
"brUCAwEAAaNgMF4wHwYDVR0jBBgwFoAU9PbBY4Yu1gGGvfRTy2R1FO8jC20wHQYD\n"\
"VR0OBBYEFEJoGM2m3Su5wOrCDbd3uEqzp5CAMAwGA1UdEwEB/wQCMAAwDgYDVR0P\n"\
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBgAbwcJTQklooMpXIPS7QAsVP4\n"\
"o69tnePGHtd8E01F2GSqe+Yjx6cY4RXU4tFeH0Ji1GYFj9CXiicv8KPPAQB7lE0S\n"\
"gV7JOL/0Hij2HI3XptGbDSdMzMOqrZCCsn0W63ujLBfThMxeU4zZChiqqqjs187K\n"\
"9eXaoDWtJM5LubVk1dEXfpq+Eg+Ro0SJ7DLpNnyOesU9TW6IKMLX0Gepx+bk/AMc\n"\
"V+14aDJJL3HSCMndSWA7yz024PGR5S0GMDWY2LTKzIZagpC0/QTB7lkJKPiHw8IV\n"\
"9iY/ZZFdkUby97nREKlSnY+Dccw6GLo6iu7FnUHTk4LtDScZ5gJCLYqlPuDG\n"\
"-----END CERTIFICATE-----"

/*
 * @brief PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 *
 * @todo If you are using AWS IoT Just in Time Registration (JITR), set this to
 * the issuer (Certificate Authority) certificate of the client certificate above.
 *
 * @note This setting is required by JITR because the issuer is used by the AWS
 * IoT gateway for routing the device's initial request. (The device client
 * certificate must always be sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html,
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set below to NULL.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM    ""

/*
 * @brief PEM-encoded client private key.
 *
 * @todo If you are running one of the Amazon FreeRTOS demo projects, set this
 * to the private key that will be used for TLS client authentication.
 *
 * @note Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */
#define keyCLIENT_PRIVATE_KEY_PEM                   \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEowIBAAKCAQEArkTwz0siKk0Q57P73OubsqNXgEfAMDv/UqHbFy5fB1p50Qio\n"\
"XhGmjVkv5YhGBgpaPdBnGPU2aV3cVtu8g8n+nyatY3JPc24cqHHooJhCZ4yj9HmA\n"\
"SRvYOiYeIX+C1T8HULKwyFSoVRCRgtPZDJFz/VVR4CcOaQ7Goc0ut9thBuEjQ3uj\n"\
"gcUrbY2YBmytMZf9V7jzoMJRwwinJql4AHMZlRscnCw4rA0cJ6/J6rCXvBviKpb4\n"\
"5ekYewvFbKSGkC2391kCP6lTnMc7TL8VDFOFp6ZKLcWE73thQDmowh9RlkMe+jNi\n"\
"xW0ORmcGrSveKmK7uIliaflw78ciCYeOBdputQIDAQABAoIBAArhixemXU++2Btf\n"\
"hY5Zt7MDt+buk/VvCZYjPQbJgm13HLwMila1S2zv8KmoRJcD9nZ9mLJaPTd/AM77\n"\
"kV25MwjE5XacIJHYgjmSQzAj0aGdim8tVvE5p9qZnrAAwi6GbPKA9cDMaGZHTo6Y\n"\
"o6jBPDjJJv+T8LZmkchwg0Y/kGNZePIfQOUnNvuVIlURW9jTc5U/MaPRNMTsN3aX\n"\
"uibzlG2lwjbp0jB6Njq/vo/2JLMKbmy2MFKoZfJlD1crdqWMsRp6Ufe6wjTdYaNJ\n"\
"CT4NDoTTy+RMI7+NIzr4EaBKUdD92sdveuT5oKb27qdN1GRk1kkKJGiR9UA31faX\n"\
"B8c5plECgYEA2lTEqxb+BovJNd9yDkI4hjmb/umLsUq9/B1kmS6X+09ZRkbR2ghx\n"\
"O03hdMHmFGO2Fpkic6dEa8LekQHfF4oCEIbQdoVXCfcN9TFVrbP0HSUBjZPwebXN\n"\
"7OnDT1bHIAe0XD4qOaexL/r5SwjfsY6VBq9gCeSi/zCkYhEXL4j1MQsCgYEAzFYN\n"\
"nc2eGHHmjA45X/yuBDY2jO0WjxHhSoQwjdK/oVLiIJ0rwVeCby4DzYuX7B+lhA1J\n"\
"qfpIC+NH31HSVS+AkjiDw2dx8pX77rrmfiyvs3c81x710rB8+7aZmLVrlLJc+fUz\n"\
"Tl/EBkv0g3J3/GwuIkZx03italp4Mm496/wuNz8CgYAUVpsveOfXAkSPIS6Fx4Nu\n"\
"dYVjnKvnqxfBmZdaca20unKNimFYFzs9FAcxkjJ1qcg3mLJN5cII69FB3tPCZJfG\n"\
"pFhdAhTWl84UDjF2CfJumJjpcGORYu8455nLFUFdaXpSsXPLhSSLXKzGYaA88RRO\n"\
"2B1xLnxEm2pkvETVp8N3ewKBgC5jQsgWS9PE18/n0sKlvGOcYxnvIPXt2zVteRBZ\n"\
"TcOz6z34MFy+HxBaY+af0Cd8r7igw55hAUYhnMln69YG6KtJRTBxJX8q6Xyy1WzD\n"\
"fEfDw/4aOzhPdLA4LfprBTdGnrDoJ3OdbgT37VSCAhc9/+MsFt8pQEUqsKrSOCCA\n"\
"qYVFAoGBAK27i3fuacu/q9T1rvh6y9BEXl+i+bPKzatk5+Gir6Etpv4d5W8mMvQx\n"\
"HIVnmTwPUq69SUIS6PvqiexZF4Nj81lM66KpNliQ8tzUsMuRIwY73Vy6ptCChnmO\n"\
"P8iOUtUQpC1TEz8C0b7KTobH0jYpCE3aZXc0Haqaaw0dLwWqrP2U\n"\
"-----END RSA PRIVATE KEY-----"

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
