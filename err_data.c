/* Copyright (c) 2015, Google Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

 /* This file was generated by err_data_generate.go. */

#include <openssl/base.h>
#include <openssl/err.h>
#include <openssl/type_check.h>


OPENSSL_STATIC_ASSERT(ERR_LIB_NONE == 1, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_SYS == 2, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_BN == 3, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_RSA == 4, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_DH == 5, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_EVP == 6, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_BUF == 7, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_OBJ == 8, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_PEM == 9, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_DSA == 10, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_X509 == 11, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_ASN1 == 12, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_CONF == 13, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_CRYPTO == 14, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_EC == 15, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_SSL == 16, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_BIO == 17, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_PKCS7 == 18, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_PKCS8 == 19, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_X509V3 == 20, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_RAND == 21, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_ENGINE == 22, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_OCSP == 23, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_UI == 24, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_COMP == 25, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_ECDSA == 26, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_ECDH == 27, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_HMAC == 28, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_DIGEST == 29, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_CIPHER == 30, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_HKDF == 31, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_TRUST_TOKEN == 32, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_LIB_USER == 33, "library value changed");
OPENSSL_STATIC_ASSERT(ERR_NUM_LIBS == 34, "number of libraries changed");

const uint32_t kOpenSSLReasonValues[] = {
    0xc320847,
    0xc328861,
    0xc330870,
    0xc338880,
    0xc34088f,
    0xc3488a8,
    0xc3508b4,
    0xc3588d1,
    0xc3608f1,
    0xc3688ff,
    0xc37090f,
    0xc37891c,
    0xc38092c,
    0xc388937,
    0xc39094d,
    0xc39895c,
    0xc3a0970,
    0xc3a8854,
    0xc3b00f7,
    0xc3b88e3,
    0x10320854,
    0x103295ca,
    0x103315d6,
    0x103395ef,
    0x10341602,
    0x10348f34,
    0x10350c6d,
    0x10359615,
    0x1036163f,
    0x10369652,
    0x10371671,
    0x1037968a,
    0x1038169f,
    0x103896bd,
    0x103916cc,
    0x103996e8,
    0x103a1703,
    0x103a9712,
    0x103b172e,
    0x103b9749,
    0x103c176f,
    0x103c80f7,
    0x103d1780,
    0x103d9794,
    0x103e17b3,
    0x103e97c2,
    0x103f17d9,
    0x103f97ec,
    0x10400c31,
    0x104097ff,
    0x1041181d,
    0x10419830,
    0x1042184a,
    0x1042985a,
    0x1043186e,
    0x10439884,
    0x1044189c,
    0x104498b1,
    0x104518c5,
    0x104598d7,
    0x1046060a,
    0x1046895c,
    0x104718ec,
    0x10479903,
    0x10481918,
    0x10489926,
    0x10490e80,
    0x10499760,
    0x104a162a,
    0x14320c14,
    0x14328c22,
    0x14330c31,
    0x14338c43,
    0x143400b9,
    0x143480f7,
    0x18320090,
    0x18328f8a,
    0x183300b9,
    0x18338fa0,
    0x18340fb4,
    0x183480f7,
    0x18350fd3,
    0x18358feb,
    0x18361000,
    0x18369014,
    0x1837104c,
    0x18379062,
    0x18381076,
    0x18389086,
    0x18390a82,
    0x18399096,
    0x183a10bc,
    0x183a90e2,
    0x183b0c8c,
    0x183b9131,
    0x183c1143,
    0x183c914e,
    0x183d115e,
    0x183d916f,
    0x183e1180,
    0x183e9192,
    0x183f11bb,
    0x183f91d4,
    0x184011ec,
    0x184086e2,
    0x18411105,
    0x184190d0,
    0x184210ef,
    0x18428c79,
    0x184310ab,
    0x18439117,
    0x18440fc9,
    0x18449038,
    0x20321226,
    0x20329213,
    0x24321232,
    0x243289a2,
    0x24331244,
    0x24339251,
    0x2434125e,
    0x24349270,
    0x2435127f,
    0x2435929c,
    0x243612a9,
    0x243692b7,
    0x243712c5,
    0x243792d3,
    0x243812dc,
    0x243892e9,
    0x243912fc,
    0x28320c61,
    0x28328c8c,
    0x28330c31,
    0x28338c9f,
    0x28340c6d,
    0x283480b9,
    0x283500f7,
    0x28358c79,
    0x2c32320f,
    0x2c329313,
    0x2c33321d,
    0x2c33b22f,
    0x2c343243,
    0x2c34b255,
    0x2c353270,
    0x2c35b282,
    0x2c3632b2,
    0x2c36833a,
    0x2c3732bf,
    0x2c37b2eb,
    0x2c383310,
    0x2c38b327,
    0x2c393345,
    0x2c39b355,
    0x2c3a3367,
    0x2c3ab37b,
    0x2c3b338c,
    0x2c3bb3ab,
    0x2c3c1325,
    0x2c3c933b,
    0x2c3d33bf,
    0x2c3d9354,
    0x2c3e33dc,
    0x2c3eb3ea,
    0x2c3f3402,
    0x2c3fb41a,
    0x2c403444,
    0x2c409226,
    0x2c413455,
    0x2c41b468,
    0x2c4211ec,
    0x2c42b479,
    0x2c43072f,
    0x2c43b39d,
    0x2c4432fe,
    0x2c44b427,
    0x2c453295,
    0x2c45b2d1,
    0x2c463335,
    0x30320000,
    0x30328015,
    0x3033001f,
    0x30338038,
    0x30340057,
    0x30348071,
    0x30350078,
    0x30358090,
    0x303600a1,
    0x303680b9,
    0x303700c6,
    0x303780d5,
    0x303800f7,
    0x30388104,
    0x30390117,
    0x30398132,
    0x303a0147,
    0x303a815b,
    0x303b016f,
    0x303b8180,
    0x303c0199,
    0x303c81b6,
    0x303d01c4,
    0x303d81d8,
    0x303e01e8,
    0x303e8201,
    0x303f0211,
    0x303f8224,
    0x30400233,
    0x3040823f,
    0x30410254,
    0x30418264,
    0x3042027b,
    0x30428288,
    0x3043029b,
    0x304382aa,
    0x304402bf,
    0x304482e0,
    0x304502f3,
    0x30458306,
    0x3046031f,
    0x3046833a,
    0x30470357,
    0x30478369,
    0x30480377,
    0x30488388,
    0x30490397,
    0x304983af,
    0x304a03c1,
    0x304a83d5,
    0x304b03ed,
    0x304b8400,
    0x304c040b,
    0x304c841c,
    0x304d0428,
    0x304d843e,
    0x304e044c,
    0x304e8462,
    0x304f0474,
    0x304f8486,
    0x305004a9,
    0x305084bc,
    0x305104cd,
    0x305184dd,
    0x305204f5,
    0x3052850a,
    0x30530522,
    0x30538536,
    0x3054054e,
    0x30548567,
    0x30550580,
    0x3055859d,
    0x305605a8,
    0x305685c0,
    0x305705d0,
    0x305785e1,
    0x305805f4,
    0x3058860a,
    0x30590613,
    0x30598628,
    0x305a063b,
    0x305a864a,
    0x305b066a,
    0x305b8679,
    0x305c069a,
    0x305c86b6,
    0x305d06c2,
    0x305d86e2,
    0x305e06fe,
    0x305e870f,
    0x305f0725,
    0x305f872f,
    0x30600499,
    0x3060804a,
    0x34320b72,
    0x34328b86,
    0x34330ba3,
    0x34338bb6,
    0x34340bc5,
    0x34348bfe,
    0x34350be2,
    0x3c320090,
    0x3c328cc9,
    0x3c330ce2,
    0x3c338cfd,
    0x3c340d1a,
    0x3c348d44,
    0x3c350d5f,
    0x3c358d85,
    0x3c360d9e,
    0x3c368db6,
    0x3c370dc7,
    0x3c378dd5,
    0x3c380de2,
    0x3c388df6,
    0x3c390c8c,
    0x3c398e19,
    0x3c3a0e2d,
    0x3c3a891c,
    0x3c3b0e3d,
    0x3c3b8e58,
    0x3c3c0e6a,
    0x3c3c8e9d,
    0x3c3d0ea7,
    0x3c3d8ebb,
    0x3c3e0ec9,
    0x3c3e8eee,
    0x3c3f0cb5,
    0x3c3f8ed7,
    0x3c4000b9,
    0x3c4080f7,
    0x3c410d35,
    0x3c418d74,
    0x3c420e80,
    0x3c428e0a,
    0x403219b8,
    0x403299ce,
    0x403319fc,
    0x40339a06,
    0x40341a1d,
    0x40349a3b,
    0x40351a4b,
    0x40359a5d,
    0x40361a6a,
    0x40369a76,
    0x40371a8b,
    0x40379a9d,
    0x40381aa8,
    0x40389aba,
    0x40390f34,
    0x40399aca,
    0x403a1add,
    0x403a9afe,
    0x403b1b0f,
    0x403b9b1f,
    0x403c0071,
    0x403c8090,
    0x403d1b80,
    0x403d9b96,
    0x403e1ba5,
    0x403e9bdd,
    0x403f1bf7,
    0x403f9c1f,
    0x40401c34,
    0x40409c48,
    0x40411c83,
    0x40419c9e,
    0x40421cb7,
    0x40429cca,
    0x40431cde,
    0x40439d0c,
    0x40441d23,
    0x404480b9,
    0x40451d38,
    0x40459d4a,
    0x40461d6e,
    0x40469d8e,
    0x40471d9c,
    0x40479dc3,
    0x40481e34,
    0x40489ee1,
    0x40491ef8,
    0x40499f12,
    0x404a1f29,
    0x404a9f47,
    0x404b1f5f,
    0x404b9f8c,
    0x404c1fa2,
    0x404c9fb4,
    0x404d1fd5,
    0x404da00e,
    0x404e2022,
    0x404ea02f,
    0x404f20ac,
    0x404fa10a,
    0x40502161,
    0x4050a175,
    0x405121a8,
    0x405221b8,
    0x4052a1dc,
    0x405321f4,
    0x4053a207,
    0x4054221c,
    0x4054a23f,
    0x4055226a,
    0x4055a2a7,
    0x405622cc,
    0x4056a2e5,
    0x405722fd,
    0x4057a310,
    0x40582325,
    0x4058a34c,
    0x4059237b,
    0x4059a3a8,
    0x405a23bc,
    0x405aa3cc,
    0x405b23e4,
    0x405ba3f5,
    0x405c2408,
    0x405ca447,
    0x405d2454,
    0x405da479,
    0x405e24b7,
    0x405e8ac0,
    0x405f24d8,
    0x405fa4e5,
    0x406024f3,
    0x4060a515,
    0x40612576,
    0x4061a5ae,
    0x406225c5,
    0x4062a5d6,
    0x40632623,
    0x4063a638,
    0x4064264f,
    0x4064a67b,
    0x40652696,
    0x4065a6ad,
    0x406626c5,
    0x4066a6ef,
    0x4067271a,
    0x4067a75f,
    0x406827a7,
    0x4068a7c8,
    0x406927fa,
    0x4069a828,
    0x406a2849,
    0x406aa869,
    0x406b29f1,
    0x406baa14,
    0x406c2a2a,
    0x406cad34,
    0x406d2d63,
    0x406dad8b,
    0x406e2db9,
    0x406eae06,
    0x406f2e5f,
    0x406fae97,
    0x40702eaa,
    0x4070aec7,
    0x4071080f,
    0x4071aed9,
    0x40722eec,
    0x4072af22,
    0x40732f3a,
    0x40739525,
    0x40742f4e,
    0x4074af68,
    0x40752f79,
    0x4075af8d,
    0x40762f9b,
    0x407692e9,
    0x40772fc0,
    0x4077b000,
    0x4078301b,
    0x4078b054,
    0x4079306b,
    0x4079b081,
    0x407a30ad,
    0x407ab0c0,
    0x407b30d5,
    0x407bb0e7,
    0x407c3118,
    0x407cb121,
    0x407d27e3,
    0x407da11a,
    0x407e3030,
    0x407ea35c,
    0x407f1db0,
    0x407f9f76,
    0x408020bc,
    0x40809dd8,
    0x408121ca,
    0x4081a060,
    0x40822da4,
    0x40829b2b,
    0x40832337,
    0x4083a660,
    0x40841dec,
    0x4084a394,
    0x40852419,
    0x4085a53d,
    0x40862499,
    0x4086a134,
    0x40872dea,
    0x4087a58b,
    0x40881b69,
    0x4088a772,
    0x40891bb8,
    0x40899b45,
    0x408a2a62,
    0x408a993d,
    0x408b30fc,
    0x408bae74,
    0x408c2429,
    0x408c9975,
    0x408d1ec7,
    0x408d9e1e,
    0x408e1ff7,
    0x408ea287,
    0x408f2786,
    0x408fa559,
    0x4090273b,
    0x4090a46b,
    0x40912a4a,
    0x4091999b,
    0x40921c05,
    0x4092ae25,
    0x40932f05,
    0x4093a145,
    0x40941e00,
    0x4094aa7b,
    0x409525e7,
    0x4095b08d,
    0x40962dd1,
    0x4096a0d5,
    0x40972190,
    0x4097a046,
    0x40981c65,
    0x4098a5fb,
    0x40992e41,
    0x4099a2b4,
    0x409a224d,
    0x409a9959,
    0x409b1e4d,
    0x409b9e78,
    0x409c2fe2,
    0x409c9ea0,
    0x409d2091,
    0x409da076,
    0x409e1cf6,
    0x409ea0f2,
    0x41f4291c,
    0x41f929ae,
    0x41fe28a1,
    0x41feab57,
    0x41ff2c85,
    0x42032935,
    0x42082957,
    0x4208a993,
    0x42092885,
    0x4209a9cd,
    0x420a28dc,
    0x420aa8bc,
    0x420b28fc,
    0x420ba975,
    0x420c2ca1,
    0x420caa8b,
    0x420d2b3e,
    0x420dab75,
    0x42122ba8,
    0x42172c68,
    0x4217abea,
    0x421c2c0c,
    0x421f2bc7,
    0x42212d19,
    0x42262c4b,
    0x422b2cf7,
    0x422bab19,
    0x422c2cd9,
    0x422caacc,
    0x422d2aa5,
    0x422dacb8,
    0x422e2af8,
    0x42302c27,
    0x4230ab8f,
    0x4432073a,
    0x44328749,
    0x44330755,
    0x44338763,
    0x44340776,
    0x44348787,
    0x4435078e,
    0x44358798,
    0x443607ab,
    0x443687c1,
    0x443707d3,
    0x443787e0,
    0x443807ef,
    0x443887f7,
    0x4439080f,
    0x4439881d,
    0x443a0830,
    0x48321313,
    0x48329325,
    0x4833133b,
    0x48339354,
    0x4c321379,
    0x4c329389,
    0x4c33139c,
    0x4c3393bc,
    0x4c3400b9,
    0x4c3480f7,
    0x4c3513c8,
    0x4c3593d6,
    0x4c3613f2,
    0x4c369418,
    0x4c371427,
    0x4c379435,
    0x4c38144a,
    0x4c389456,
    0x4c391476,
    0x4c3994a0,
    0x4c3a14b9,
    0x4c3a94d2,
    0x4c3b060a,
    0x4c3b94eb,
    0x4c3c14fd,
    0x4c3c950c,
    0x4c3d1525,
    0x4c3d8c54,
    0x4c3e1592,
    0x4c3e9534,
    0x4c3f15b4,
    0x4c3f92e9,
    0x4c40154a,
    0x4c409365,
    0x4c411582,
    0x4c419405,
    0x4c42156e,
    0x5032348b,
    0x5032b49a,
    0x503334a5,
    0x5033b4b5,
    0x503434ce,
    0x5034b4e8,
    0x503534f6,
    0x5035b50c,
    0x5036351e,
    0x5036b534,
    0x5037354d,
    0x5037b560,
    0x50383578,
    0x5038b589,
    0x5039359e,
    0x5039b5b2,
    0x503a35d2,
    0x503ab5e8,
    0x503b3600,
    0x503bb612,
    0x503c362e,
    0x503cb645,
    0x503d365e,
    0x503db674,
    0x503e3681,
    0x503eb697,
    0x503f36a9,
    0x503f8388,
    0x504036bc,
    0x5040b6cc,
    0x504136e6,
    0x5041b6f5,
    0x5042370f,
    0x5042b72c,
    0x5043373c,
    0x5043b74c,
    0x5044375b,
    0x5044843e,
    0x5045376f,
    0x5045b78d,
    0x504637a0,
    0x5046b7b6,
    0x504737c8,
    0x5047b7dd,
    0x50483803,
    0x5048b811,
    0x50493824,
    0x5049b839,
    0x504a384f,
    0x504ab85f,
    0x504b387f,
    0x504bb892,
    0x504c38b5,
    0x504cb8e3,
    0x504d38f5,
    0x504db912,
    0x504e392d,
    0x504eb949,
    0x504f395b,
    0x504fb972,
    0x50503981,
    0x505086fe,
    0x50513994,
    0x58320f72,
    0x68320f34,
    0x68328c8c,
    0x68330c9f,
    0x68338f42,
    0x68340f52,
    0x683480f7,
    0x6c320efa,
    0x6c328c43,
    0x6c330f05,
    0x6c338f1e,
    0x74320a28,
    0x743280b9,
    0x74330c54,
    0x7832098d,
    0x783289a2,
    0x783309ae,
    0x78338090,
    0x783409bd,
    0x783489d2,
    0x783509f1,
    0x78358a13,
    0x78360a28,
    0x78368a3e,
    0x78370a4e,
    0x78378a6f,
    0x78380a82,
    0x78388a94,
    0x78390aa1,
    0x78398ac0,
    0x783a0ad5,
    0x783a8ae3,
    0x783b0aed,
    0x783b8b01,
    0x783c0b18,
    0x783c8b2d,
    0x783d0b44,
    0x783d8b59,
    0x783e0aaf,
    0x783e8a61,
    0x7c321202,
    0x80321418,
    0x80328090,
    0x803331de,
    0x803380b9,
    0x803431ed,
    0x8034b155,
    0x80353173,
    0x8035b201,
    0x803631b5,
    0x8036b164,
    0x803731a7,
    0x8037b142,
    0x803831c8,
    0x8038b184,
    0x80393199,
};

const size_t kOpenSSLReasonValuesLen = sizeof(kOpenSSLReasonValues) / sizeof(kOpenSSLReasonValues[0]);

const char kOpenSSLReasonStringData[] =
    "ASN1_LENGTH_MISMATCH\0"
    "AUX_ERROR\0"
    "BAD_GET_ASN1_OBJECT_CALL\0"
    "BAD_OBJECT_HEADER\0"
    "BAD_TEMPLATE\0"
    "BMPSTRING_IS_WRONG_LENGTH\0"
    "BN_LIB\0"
    "BOOLEAN_IS_WRONG_LENGTH\0"
    "BUFFER_TOO_SMALL\0"
    "CONTEXT_NOT_INITIALISED\0"
    "DECODE_ERROR\0"
    "DEPTH_EXCEEDED\0"
    "DIGEST_AND_KEY_TYPE_NOT_SUPPORTED\0"
    "ENCODE_ERROR\0"
    "ERROR_GETTING_TIME\0"
    "EXPECTING_AN_ASN1_SEQUENCE\0"
    "EXPECTING_AN_INTEGER\0"
    "EXPECTING_AN_OBJECT\0"
    "EXPECTING_A_BOOLEAN\0"
    "EXPECTING_A_TIME\0"
    "EXPLICIT_LENGTH_MISMATCH\0"
    "EXPLICIT_TAG_NOT_CONSTRUCTED\0"
    "FIELD_MISSING\0"
    "FIRST_NUM_TOO_LARGE\0"
    "HEADER_TOO_LONG\0"
    "ILLEGAL_BITSTRING_FORMAT\0"
    "ILLEGAL_BOOLEAN\0"
    "ILLEGAL_CHARACTERS\0"
    "ILLEGAL_FORMAT\0"
    "ILLEGAL_HEX\0"
    "ILLEGAL_IMPLICIT_TAG\0"
    "ILLEGAL_INTEGER\0"
    "ILLEGAL_NESTED_TAGGING\0"
    "ILLEGAL_NULL\0"
    "ILLEGAL_NULL_VALUE\0"
    "ILLEGAL_OBJECT\0"
    "ILLEGAL_OPTIONAL_ANY\0"
    "ILLEGAL_OPTIONS_ON_ITEM_TEMPLATE\0"
    "ILLEGAL_TAGGED_ANY\0"
    "ILLEGAL_TIME_VALUE\0"
    "INTEGER_NOT_ASCII_FORMAT\0"
    "INTEGER_TOO_LARGE_FOR_LONG\0"
    "INVALID_BIT_STRING_BITS_LEFT\0"
    "INVALID_BMPSTRING\0"
    "INVALID_DIGIT\0"
    "INVALID_MODIFIER\0"
    "INVALID_NUMBER\0"
    "INVALID_OBJECT_ENCODING\0"
    "INVALID_SEPARATOR\0"
    "INVALID_TIME_FORMAT\0"
    "INVALID_UNIVERSALSTRING\0"
    "INVALID_UTF8STRING\0"
    "LIST_ERROR\0"
    "MISSING_ASN1_EOS\0"
    "MISSING_EOC\0"
    "MISSING_SECOND_NUMBER\0"
    "MISSING_VALUE\0"
    "MSTRING_NOT_UNIVERSAL\0"
    "MSTRING_WRONG_TAG\0"
    "NESTED_ASN1_ERROR\0"
    "NESTED_ASN1_STRING\0"
    "NESTED_TOO_DEEP\0"
    "NON_HEX_CHARACTERS\0"
    "NOT_ASCII_FORMAT\0"
    "NOT_ENOUGH_DATA\0"
    "NO_MATCHING_CHOICE_TYPE\0"
    "NULL_IS_WRONG_LENGTH\0"
    "OBJECT_NOT_ASCII_FORMAT\0"
    "ODD_NUMBER_OF_CHARS\0"
    "SECOND_NUMBER_TOO_LARGE\0"
    "SEQUENCE_LENGTH_MISMATCH\0"
    "SEQUENCE_NOT_CONSTRUCTED\0"
    "SEQUENCE_OR_SET_NEEDS_CONFIG\0"
    "SHORT_LINE\0"
    "STREAMING_NOT_SUPPORTED\0"
    "STRING_TOO_LONG\0"
    "STRING_TOO_SHORT\0"
    "TAG_VALUE_TOO_HIGH\0"
    "TIME_NOT_ASCII_FORMAT\0"
    "TOO_LONG\0"
    "TYPE_NOT_CONSTRUCTED\0"
    "TYPE_NOT_PRIMITIVE\0"
    "UNEXPECTED_EOC\0"
    "UNIVERSALSTRING_IS_WRONG_LENGTH\0"
    "UNKNOWN_FORMAT\0"
    "UNKNOWN_MESSAGE_DIGEST_ALGORITHM\0"
    "UNKNOWN_SIGNATURE_ALGORITHM\0"
    "UNKNOWN_TAG\0"
    "UNSUPPORTED_ANY_DEFINED_BY_TYPE\0"
    "UNSUPPORTED_PUBLIC_KEY_TYPE\0"
    "UNSUPPORTED_TYPE\0"
    "WRONG_PUBLIC_KEY_TYPE\0"
    "WRONG_TAG\0"
    "WRONG_TYPE\0"
    "BAD_FOPEN_MODE\0"
    "BROKEN_PIPE\0"
    "CONNECT_ERROR\0"
    "ERROR_SETTING_NBIO\0"
    "INVALID_ARGUMENT\0"
    "IN_USE\0"
    "KEEPALIVE\0"
    "NBIO_CONNECT_ERROR\0"
    "NO_HOSTNAME_SPECIFIED\0"
    "NO_PORT_SPECIFIED\0"
    "NO_SUCH_FILE\0"
    "NULL_PARAMETER\0"
    "SYS_LIB\0"
    "UNABLE_TO_CREATE_SOCKET\0"
    "UNINITIALIZED\0"
    "UNSUPPORTED_METHOD\0"
    "WRITE_TO_READ_ONLY_BIO\0"
    "ARG2_LT_ARG3\0"
    "BAD_ENCODING\0"
    "BAD_RECIPROCAL\0"
    "BIGNUM_TOO_LONG\0"
    "BITS_TOO_SMALL\0"
    "CALLED_WITH_EVEN_MODULUS\0"
    "DIV_BY_ZERO\0"
    "EXPAND_ON_STATIC_BIGNUM_DATA\0"
    "INPUT_NOT_REDUCED\0"
    "INVALID_INPUT\0"
    "INVALID_RANGE\0"
    "NEGATIVE_NUMBER\0"
    "NOT_A_SQUARE\0"
    "NOT_INITIALIZED\0"
    "NO_INVERSE\0"
    "PRIVATE_KEY_TOO_LARGE\0"
    "P_IS_NOT_PRIME\0"
    "TOO_MANY_ITERATIONS\0"
    "TOO_MANY_TEMPORARY_VARIABLES\0"
    "AES_KEY_SETUP_FAILED\0"
    "BAD_DECRYPT\0"
    "BAD_KEY_LENGTH\0"
    "CTRL_NOT_IMPLEMENTED\0"
    "CTRL_OPERATION_NOT_IMPLEMENTED\0"
    "DATA_NOT_MULTIPLE_OF_BLOCK_LENGTH\0"
    "INITIALIZATION_ERROR\0"
    "INPUT_NOT_INITIALIZED\0"
    "INVALID_AD_SIZE\0"
    "INVALID_KEY_LENGTH\0"
    "INVALID_NONCE\0"
    "INVALID_NONCE_SIZE\0"
    "INVALID_OPERATION\0"
    "IV_TOO_LARGE\0"
    "NO_CIPHER_SET\0"
    "NO_DIRECTION_SET\0"
    "OUTPUT_ALIASES_INPUT\0"
    "TAG_TOO_LARGE\0"
    "TOO_LARGE\0"
    "UNSUPPORTED_AD_SIZE\0"
    "UNSUPPORTED_INPUT_SIZE\0"
    "UNSUPPORTED_KEY_SIZE\0"
    "UNSUPPORTED_NONCE_SIZE\0"
    "UNSUPPORTED_TAG_SIZE\0"
    "WRONG_FINAL_BLOCK_LENGTH\0"
    "LIST_CANNOT_BE_NULL\0"
    "MISSING_CLOSE_SQUARE_BRACKET\0"
    "MISSING_EQUAL_SIGN\0"
    "NO_CLOSE_BRACE\0"
    "UNABLE_TO_CREATE_NEW_SECTION\0"
    "VARIABLE_EXPANSION_TOO_LONG\0"
    "VARIABLE_HAS_NO_VALUE\0"
    "BAD_GENERATOR\0"
    "INVALID_PUBKEY\0"
    "MODULUS_TOO_LARGE\0"
    "NO_PRIVATE_VALUE\0"
    "UNKNOWN_HASH\0"
    "BAD_Q_VALUE\0"
    "BAD_VERSION\0"
    "INVALID_PARAMETERS\0"
    "MISSING_PARAMETERS\0"
    "NEED_NEW_SETUP_VALUES\0"
    "BIGNUM_OUT_OF_RANGE\0"
    "COORDINATES_OUT_OF_RANGE\0"
    "D2I_ECPKPARAMETERS_FAILURE\0"
    "EC_GROUP_NEW_BY_NAME_FAILURE\0"
    "GROUP2PKPARAMETERS_FAILURE\0"
    "GROUP_MISMATCH\0"
    "I2D_ECPKPARAMETERS_FAILURE\0"
    "INCOMPATIBLE_OBJECTS\0"
    "INVALID_COFACTOR\0"
    "INVALID_COMPRESSED_POINT\0"
    "INVALID_COMPRESSION_BIT\0"
    "INVALID_ENCODING\0"
    "INVALID_FIELD\0"
    "INVALID_FORM\0"
    "INVALID_GROUP_ORDER\0"
    "INVALID_PRIVATE_KEY\0"
    "INVALID_SCALAR\0"
    "MISSING_PRIVATE_KEY\0"
    "NON_NAMED_CURVE\0"
    "PKPARAMETERS2GROUP_FAILURE\0"
    "POINT_AT_INFINITY\0"
    "POINT_IS_NOT_ON_CURVE\0"
    "PUBLIC_KEY_VALIDATION_FAILED\0"
    "SLOT_FULL\0"
    "UNDEFINED_GENERATOR\0"
    "UNKNOWN_GROUP\0"
    "UNKNOWN_ORDER\0"
    "WRONG_CURVE_PARAMETERS\0"
    "WRONG_ORDER\0"
    "KDF_FAILED\0"
    "POINT_ARITHMETIC_FAILURE\0"
    "UNKNOWN_DIGEST_LENGTH\0"
    "BAD_SIGNATURE\0"
    "NOT_IMPLEMENTED\0"
    "RANDOM_NUMBER_GENERATION_FAILED\0"
    "OPERATION_NOT_SUPPORTED\0"
    "COMMAND_NOT_SUPPORTED\0"
    "DIFFERENT_KEY_TYPES\0"
    "DIFFERENT_PARAMETERS\0"
    "EMPTY_PSK\0"
    "EXPECTING_AN_EC_KEY_KEY\0"
    "EXPECTING_AN_RSA_KEY\0"
    "EXPECTING_A_DSA_KEY\0"
    "ILLEGAL_OR_UNSUPPORTED_PADDING_MODE\0"
    "INVALID_BUFFER_SIZE\0"
    "INVALID_DIGEST_LENGTH\0"
    "INVALID_DIGEST_TYPE\0"
    "INVALID_KEYBITS\0"
    "INVALID_MGF1_MD\0"
    "INVALID_PADDING_MODE\0"
    "INVALID_PEER_KEY\0"
    "INVALID_PSS_SALTLEN\0"
    "INVALID_SIGNATURE\0"
    "KEYS_NOT_SET\0"
    "MEMORY_LIMIT_EXCEEDED\0"
    "NOT_A_PRIVATE_KEY\0"
    "NOT_XOF_OR_INVALID_LENGTH\0"
    "NO_DEFAULT_DIGEST\0"
    "NO_KEY_SET\0"
    "NO_MDC2_SUPPORT\0"
    "NO_NID_FOR_CURVE\0"
    "NO_OPERATION_SET\0"
    "NO_PARAMETERS_SET\0"
    "OPERATION_NOT_SUPPORTED_FOR_THIS_KEYTYPE\0"
    "OPERATON_NOT_INITIALIZED\0"
    "UNKNOWN_PUBLIC_KEY_TYPE\0"
    "UNSUPPORTED_ALGORITHM\0"
    "OUTPUT_TOO_LARGE\0"
    "INVALID_OID_STRING\0"
    "UNKNOWN_NID\0"
    "BAD_BASE64_DECODE\0"
    "BAD_END_LINE\0"
    "BAD_IV_CHARS\0"
    "BAD_PASSWORD_READ\0"
    "CIPHER_IS_NULL\0"
    "ERROR_CONVERTING_PRIVATE_KEY\0"
    "NOT_DEK_INFO\0"
    "NOT_ENCRYPTED\0"
    "NOT_PROC_TYPE\0"
    "NO_START_LINE\0"
    "READ_KEY\0"
    "SHORT_HEADER\0"
    "UNSUPPORTED_CIPHER\0"
    "UNSUPPORTED_ENCRYPTION\0"
    "BAD_PKCS7_VERSION\0"
    "NOT_PKCS7_SIGNED_DATA\0"
    "NO_CERTIFICATES_INCLUDED\0"
    "NO_CRLS_INCLUDED\0"
    "BAD_ITERATION_COUNT\0"
    "BAD_PKCS12_DATA\0"
    "BAD_PKCS12_VERSION\0"
    "CIPHER_HAS_NO_OBJECT_IDENTIFIER\0"
    "CRYPT_ERROR\0"
    "ENCRYPT_ERROR\0"
    "ERROR_SETTING_CIPHER_PARAMS\0"
    "INCORRECT_PASSWORD\0"
    "INVALID_CHARACTERS\0"
    "KEYGEN_FAILURE\0"
    "KEY_GEN_ERROR\0"
    "METHOD_NOT_SUPPORTED\0"
    "MISSING_MAC\0"
    "MULTIPLE_PRIVATE_KEYS_IN_PKCS12\0"
    "PKCS12_PUBLIC_KEY_INTEGRITY_NOT_SUPPORTED\0"
    "PKCS12_TOO_DEEPLY_NESTED\0"
    "PRIVATE_KEY_DECODE_ERROR\0"
    "PRIVATE_KEY_ENCODE_ERROR\0"
    "UNKNOWN_ALGORITHM\0"
    "UNKNOWN_CIPHER\0"
    "UNKNOWN_CIPHER_ALGORITHM\0"
    "UNKNOWN_DIGEST\0"
    "UNSUPPORTED_KEYLENGTH\0"
    "UNSUPPORTED_KEY_DERIVATION_FUNCTION\0"
    "UNSUPPORTED_OPTIONS\0"
    "UNSUPPORTED_PRF\0"
    "UNSUPPORTED_PRIVATE_KEY_ALGORITHM\0"
    "UNSUPPORTED_SALT_TYPE\0"
    "BAD_E_VALUE\0"
    "BAD_FIXED_HEADER_DECRYPT\0"
    "BAD_PAD_BYTE_COUNT\0"
    "BAD_RSA_PARAMETERS\0"
    "BLOCK_TYPE_IS_NOT_01\0"
    "BLOCK_TYPE_IS_NOT_02\0"
    "BN_NOT_INITIALIZED\0"
    "CANNOT_RECOVER_MULTI_PRIME_KEY\0"
    "CRT_PARAMS_ALREADY_GIVEN\0"
    "CRT_VALUES_INCORRECT\0"
    "DATA_LEN_NOT_EQUAL_TO_MOD_LEN\0"
    "DATA_TOO_LARGE\0"
    "DATA_TOO_LARGE_FOR_KEY_SIZE\0"
    "DATA_TOO_LARGE_FOR_MODULUS\0"
    "DATA_TOO_SMALL\0"
    "DATA_TOO_SMALL_FOR_KEY_SIZE\0"
    "DIGEST_TOO_BIG_FOR_RSA_KEY\0"
    "D_E_NOT_CONGRUENT_TO_1\0"
    "D_OUT_OF_RANGE\0"
    "EMPTY_PUBLIC_KEY\0"
    "FIRST_OCTET_INVALID\0"
    "INCONSISTENT_SET_OF_CRT_VALUES\0"
    "INTERNAL_ERROR\0"
    "INVALID_MESSAGE_LENGTH\0"
    "KEY_SIZE_TOO_SMALL\0"
    "LAST_OCTET_INVALID\0"
    "MUST_HAVE_AT_LEAST_TWO_PRIMES\0"
    "NO_PUBLIC_EXPONENT\0"
    "NULL_BEFORE_BLOCK_MISSING\0"
    "N_NOT_EQUAL_P_Q\0"
    "OAEP_DECODING_ERROR\0"
    "ONLY_ONE_OF_P_Q_GIVEN\0"
    "OUTPUT_BUFFER_TOO_SMALL\0"
    "PADDING_CHECK_FAILED\0"
    "PKCS_DECODING_ERROR\0"
    "SLEN_CHECK_FAILED\0"
    "SLEN_RECOVERY_FAILED\0"
    "UNKNOWN_ALGORITHM_TYPE\0"
    "UNKNOWN_PADDING_TYPE\0"
    "VALUE_MISSING\0"
    "WRONG_SIGNATURE_LENGTH\0"
    "ALPN_MISMATCH_ON_EARLY_DATA\0"
    "ALPS_MISMATCH_ON_EARLY_DATA\0"
    "APPLICATION_DATA_INSTEAD_OF_HANDSHAKE\0"
    "APPLICATION_DATA_ON_SHUTDOWN\0"
    "APP_DATA_IN_HANDSHAKE\0"
    "ATTEMPT_TO_REUSE_SESSION_IN_DIFFERENT_CONTEXT\0"
    "BAD_ALERT\0"
    "BAD_CHANGE_CIPHER_SPEC\0"
    "BAD_DATA_RETURNED_BY_CALLBACK\0"
    "BAD_DH_P_LENGTH\0"
    "BAD_DIGEST_LENGTH\0"
    "BAD_ECC_CERT\0"
    "BAD_ECPOINT\0"
    "BAD_HANDSHAKE_RECORD\0"
    "BAD_HELLO_REQUEST\0"
    "BAD_LENGTH\0"
    "BAD_PACKET_LENGTH\0"
    "BAD_RSA_ENCRYPT\0"
    "BAD_SRTP_MKI_VALUE\0"
    "BAD_SRTP_PROTECTION_PROFILE_LIST\0"
    "BAD_SSL_FILETYPE\0"
    "BAD_WRITE_RETRY\0"
    "BIO_NOT_SET\0"
    "BLOCK_CIPHER_PAD_IS_WRONG\0"
    "CANNOT_HAVE_BOTH_PRIVKEY_AND_METHOD\0"
    "CANNOT_PARSE_LEAF_CERT\0"
    "CA_DN_LENGTH_MISMATCH\0"
    "CA_DN_TOO_LONG\0"
    "CCS_RECEIVED_EARLY\0"
    "CERTIFICATE_AND_PRIVATE_KEY_MISMATCH\0"
    "CERTIFICATE_VERIFY_FAILED\0"
    "CERT_CB_ERROR\0"
    "CERT_DECOMPRESSION_FAILED\0"
    "CERT_LENGTH_MISMATCH\0"
    "CHANNEL_ID_NOT_P256\0"
    "CHANNEL_ID_SIGNATURE_INVALID\0"
    "CIPHER_MISMATCH_ON_EARLY_DATA\0"
    "CIPHER_OR_HASH_UNAVAILABLE\0"
    "CLIENTHELLO_PARSE_FAILED\0"
    "CLIENTHELLO_TLSEXT\0"
    "CONNECTION_REJECTED\0"
    "CONNECTION_TYPE_NOT_SET\0"
    "COULD_NOT_PARSE_HINTS\0"
    "CUSTOM_EXTENSION_ERROR\0"
    "DATA_LENGTH_TOO_LONG\0"
    "DECRYPTION_FAILED\0"
    "DECRYPTION_FAILED_OR_BAD_RECORD_MAC\0"
    "DH_PUBLIC_VALUE_LENGTH_IS_WRONG\0"
    "DH_P_TOO_LONG\0"
    "DIGEST_CHECK_FAILED\0"
    "DOWNGRADE_DETECTED\0"
    "DTLS_MESSAGE_TOO_BIG\0"
    "DUPLICATE_EXTENSION\0"
    "DUPLICATE_KEY_SHARE\0"
    "DUPLICATE_SIGNATURE_ALGORITHM\0"
    "EARLY_DATA_NOT_IN_USE\0"
    "ECC_CERT_NOT_FOR_SIGNING\0"
    "ECH_SERVER_CONFIG_AND_PRIVATE_KEY_MISMATCH\0"
    "ECH_SERVER_CONFIG_UNSUPPORTED_EXTENSION\0"
    "ECH_SERVER_WOULD_HAVE_NO_RETRY_CONFIGS\0"
    "EMPTY_HELLO_RETRY_REQUEST\0"
    "EMS_STATE_INCONSISTENT\0"
    "ENCRYPTED_LENGTH_TOO_LONG\0"
    "ERROR_ADDING_EXTENSION\0"
    "ERROR_IN_RECEIVED_CIPHER_LIST\0"
    "ERROR_PARSING_EXTENSION\0"
    "EXCESSIVE_MESSAGE_SIZE\0"
    "EXCESS_HANDSHAKE_DATA\0"
    "EXTRA_DATA_IN_MESSAGE\0"
    "FRAGMENT_MISMATCH\0"
    "GOT_NEXT_PROTO_WITHOUT_EXTENSION\0"
    "HANDSHAKE_FAILURE_ON_CLIENT_HELLO\0"
    "HANDSHAKE_NOT_COMPLETE\0"
    "HTTPS_PROXY_REQUEST\0"
    "HTTP_REQUEST\0"
    "INAPPROPRIATE_FALLBACK\0"
    "INCONSISTENT_CLIENT_HELLO\0"
    "INVALID_ALPN_PROTOCOL\0"
    "INVALID_ALPN_PROTOCOL_LIST\0"
    "INVALID_CLIENT_HELLO_INNER\0"
    "INVALID_COMMAND\0"
    "INVALID_COMPRESSION_LIST\0"
    "INVALID_DELEGATED_CREDENTIAL\0"
    "INVALID_ECH_PUBLIC_NAME\0"
    "INVALID_MESSAGE\0"
    "INVALID_OUTER_RECORD_TYPE\0"
    "INVALID_SCT_LIST\0"
    "INVALID_SIGNATURE_ALGORITHM\0"
    "INVALID_SSL_SESSION\0"
    "INVALID_TICKET_KEYS_LENGTH\0"
    "KEY_USAGE_BIT_INCORRECT\0"
    "LENGTH_MISMATCH\0"
    "MISSING_EXTENSION\0"
    "MISSING_KEY_SHARE\0"
    "MISSING_RSA_CERTIFICATE\0"
    "MISSING_TMP_DH_KEY\0"
    "MISSING_TMP_ECDH_KEY\0"
    "MIXED_SPECIAL_OPERATOR_WITH_GROUPS\0"
    "MTU_TOO_SMALL\0"
    "NEGOTIATED_ALPS_WITHOUT_ALPN\0"
    "NEGOTIATED_BOTH_NPN_AND_ALPN\0"
    "NEGOTIATED_TB_WITHOUT_EMS_OR_RI\0"
    "NESTED_GROUP\0"
    "NO_APPLICATION_PROTOCOL\0"
    "NO_CERTIFICATES_RETURNED\0"
    "NO_CERTIFICATE_ASSIGNED\0"
    "NO_CERTIFICATE_SET\0"
    "NO_CIPHERS_AVAILABLE\0"
    "NO_CIPHERS_PASSED\0"
    "NO_CIPHERS_SPECIFIED\0"
    "NO_CIPHER_MATCH\0"
    "NO_COMMON_SIGNATURE_ALGORITHMS\0"
    "NO_COMPRESSION_SPECIFIED\0"
    "NO_GROUPS_SPECIFIED\0"
    "NO_METHOD_SPECIFIED\0"
    "NO_P256_SUPPORT\0"
    "NO_PRIVATE_KEY_ASSIGNED\0"
    "NO_RENEGOTIATION\0"
    "NO_REQUIRED_DIGEST\0"
    "NO_SHARED_CIPHER\0"
    "NO_SHARED_GROUP\0"
    "NO_SUPPORTED_VERSIONS_ENABLED\0"
    "NULL_SSL_CTX\0"
    "NULL_SSL_METHOD_PASSED\0"
    "OCSP_CB_ERROR\0"
    "OLD_SESSION_CIPHER_NOT_RETURNED\0"
    "OLD_SESSION_PRF_HASH_MISMATCH\0"
    "OLD_SESSION_VERSION_NOT_RETURNED\0"
    "PARSE_TLSEXT\0"
    "PATH_TOO_LONG\0"
    "PEER_DID_NOT_RETURN_A_CERTIFICATE\0"
    "PEER_ERROR_UNSUPPORTED_CERTIFICATE_TYPE\0"
    "PRE_SHARED_KEY_MUST_BE_LAST\0"
    "PRIVATE_KEY_OPERATION_FAILED\0"
    "PROTOCOL_IS_SHUTDOWN\0"
    "PSK_IDENTITY_BINDER_COUNT_MISMATCH\0"
    "PSK_IDENTITY_NOT_FOUND\0"
    "PSK_NO_CLIENT_CB\0"
    "PSK_NO_SERVER_CB\0"
    "QUIC_INTERNAL_ERROR\0"
    "QUIC_TRANSPORT_PARAMETERS_MISCONFIGURED\0"
    "READ_TIMEOUT_EXPIRED\0"
    "RECORD_LENGTH_MISMATCH\0"
    "RECORD_TOO_LARGE\0"
    "RENEGOTIATION_EMS_MISMATCH\0"
    "RENEGOTIATION_ENCODING_ERR\0"
    "RENEGOTIATION_MISMATCH\0"
    "REQUIRED_CIPHER_MISSING\0"
    "RESUMED_EMS_SESSION_WITHOUT_EMS_EXTENSION\0"
    "RESUMED_NON_EMS_SESSION_WITH_EMS_EXTENSION\0"
    "SCSV_RECEIVED_WHEN_RENEGOTIATING\0"
    "SECOND_SERVERHELLO_VERSION_MISMATCH\0"
    "SERVERHELLO_TLSEXT\0"
    "SERVER_CERT_CHANGED\0"
    "SERVER_ECHOED_INVALID_SESSION_ID\0"
    "SESSION_ID_CONTEXT_UNINITIALIZED\0"
    "SESSION_MAY_NOT_BE_CREATED\0"
    "SHUTDOWN_WHILE_IN_INIT\0"
    "SIGNATURE_ALGORITHMS_EXTENSION_SENT_BY_SERVER\0"
    "SRTP_COULD_NOT_ALLOCATE_PROFILES\0"
    "SRTP_UNKNOWN_PROTECTION_PROFILE\0"
    "SSL3_EXT_INVALID_SERVERNAME\0"
    "SSLV3_ALERT_BAD_CERTIFICATE\0"
    "SSLV3_ALERT_BAD_RECORD_MAC\0"
    "SSLV3_ALERT_CERTIFICATE_EXPIRED\0"
    "SSLV3_ALERT_CERTIFICATE_REVOKED\0"
    "SSLV3_ALERT_CERTIFICATE_UNKNOWN\0"
    "SSLV3_ALERT_CLOSE_NOTIFY\0"
    "SSLV3_ALERT_DECOMPRESSION_FAILURE\0"
    "SSLV3_ALERT_HANDSHAKE_FAILURE\0"
    "SSLV3_ALERT_ILLEGAL_PARAMETER\0"
    "SSLV3_ALERT_NO_CERTIFICATE\0"
    "SSLV3_ALERT_UNEXPECTED_MESSAGE\0"
    "SSLV3_ALERT_UNSUPPORTED_CERTIFICATE\0"
    "SSL_CTX_HAS_NO_DEFAULT_SSL_VERSION\0"
    "SSL_HANDSHAKE_FAILURE\0"
    "SSL_SESSION_ID_CONTEXT_TOO_LONG\0"
    "SSL_SESSION_ID_TOO_LONG\0"
    "TICKET_ENCRYPTION_FAILED\0"
    "TLS13_DOWNGRADE\0"
    "TLSV1_ALERT_ACCESS_DENIED\0"
    "TLSV1_ALERT_BAD_CERTIFICATE_HASH_VALUE\0"
    "TLSV1_ALERT_BAD_CERTIFICATE_STATUS_RESPONSE\0"
    "TLSV1_ALERT_CERTIFICATE_REQUIRED\0"
    "TLSV1_ALERT_CERTIFICATE_UNOBTAINABLE\0"
    "TLSV1_ALERT_DECODE_ERROR\0"
    "TLSV1_ALERT_DECRYPTION_FAILED\0"
    "TLSV1_ALERT_DECRYPT_ERROR\0"
    "TLSV1_ALERT_ECH_REQUIRED\0"
    "TLSV1_ALERT_EXPORT_RESTRICTION\0"
    "TLSV1_ALERT_INAPPROPRIATE_FALLBACK\0"
    "TLSV1_ALERT_INSUFFICIENT_SECURITY\0"
    "TLSV1_ALERT_INTERNAL_ERROR\0"
    "TLSV1_ALERT_NO_APPLICATION_PROTOCOL\0"
    "TLSV1_ALERT_NO_RENEGOTIATION\0"
    "TLSV1_ALERT_PROTOCOL_VERSION\0"
    "TLSV1_ALERT_RECORD_OVERFLOW\0"
    "TLSV1_ALERT_UNKNOWN_CA\0"
    "TLSV1_ALERT_UNKNOWN_PSK_IDENTITY\0"
    "TLSV1_ALERT_UNRECOGNIZED_NAME\0"
    "TLSV1_ALERT_UNSUPPORTED_EXTENSION\0"
    "TLSV1_ALERT_USER_CANCELLED\0"
    "TLS_PEER_DID_NOT_RESPOND_WITH_CERTIFICATE_LIST\0"
    "TLS_RSA_ENCRYPTED_VALUE_LENGTH_IS_WRONG\0"
    "TOO_MANY_EMPTY_FRAGMENTS\0"
    "TOO_MANY_KEY_UPDATES\0"
    "TOO_MANY_WARNING_ALERTS\0"
    "TOO_MUCH_READ_EARLY_DATA\0"
    "TOO_MUCH_SKIPPED_EARLY_DATA\0"
    "UNABLE_TO_FIND_ECDH_PARAMETERS\0"
    "UNCOMPRESSED_CERT_TOO_LARGE\0"
    "UNEXPECTED_COMPATIBILITY_MODE\0"
    "UNEXPECTED_EXTENSION\0"
    "UNEXPECTED_EXTENSION_ON_EARLY_DATA\0"
    "UNEXPECTED_MESSAGE\0"
    "UNEXPECTED_OPERATOR_IN_GROUP\0"
    "UNEXPECTED_RECORD\0"
    "UNKNOWN_ALERT_TYPE\0"
    "UNKNOWN_CERTIFICATE_TYPE\0"
    "UNKNOWN_CERT_COMPRESSION_ALG\0"
    "UNKNOWN_CIPHER_RETURNED\0"
    "UNKNOWN_CIPHER_TYPE\0"
    "UNKNOWN_KEY_EXCHANGE_TYPE\0"
    "UNKNOWN_PROTOCOL\0"
    "UNKNOWN_SSL_VERSION\0"
    "UNKNOWN_STATE\0"
    "UNSAFE_LEGACY_RENEGOTIATION_DISABLED\0"
    "UNSUPPORTED_COMPRESSION_ALGORITHM\0"
    "UNSUPPORTED_ECH_SERVER_CONFIG\0"
    "UNSUPPORTED_ELLIPTIC_CURVE\0"
    "UNSUPPORTED_PROTOCOL\0"
    "UNSUPPORTED_PROTOCOL_FOR_CUSTOM_KEY\0"
    "WRONG_CERTIFICATE_TYPE\0"
    "WRONG_CIPHER_RETURNED\0"
    "WRONG_CURVE\0"
    "WRONG_ENCRYPTION_LEVEL_RECEIVED\0"
    "WRONG_MESSAGE_TYPE\0"
    "WRONG_SIGNATURE_TYPE\0"
    "WRONG_SSL_VERSION\0"
    "WRONG_VERSION_NUMBER\0"
    "WRONG_VERSION_ON_EARLY_DATA\0"
    "X509_LIB\0"
    "X509_VERIFICATION_SETUP_PROBLEMS\0"
    "BAD_VALIDITY_CHECK\0"
    "DECODE_FAILURE\0"
    "INVALID_KEY_ID\0"
    "INVALID_METADATA\0"
    "INVALID_METADATA_KEY\0"
    "INVALID_PROOF\0"
    "INVALID_TOKEN\0"
    "NO_KEYS_CONFIGURED\0"
    "NO_SRR_KEY_CONFIGURED\0"
    "OVER_BATCHSIZE\0"
    "SRR_SIGNATURE_ERROR\0"
    "TOO_MANY_KEYS\0"
    "AKID_MISMATCH\0"
    "BAD_X509_FILETYPE\0"
    "BASE64_DECODE_ERROR\0"
    "CANT_CHECK_DH_KEY\0"
    "CERT_ALREADY_IN_HASH_TABLE\0"
    "CRL_ALREADY_DELTA\0"
    "CRL_VERIFY_FAILURE\0"
    "DELTA_CRL_WITHOUT_CRL_NUMBER\0"
    "IDP_MISMATCH\0"
    "INVALID_DIRECTORY\0"
    "INVALID_FIELD_FOR_VERSION\0"
    "INVALID_FIELD_NAME\0"
    "INVALID_PARAMETER\0"
    "INVALID_PSS_PARAMETERS\0"
    "INVALID_TRUST\0"
    "INVALID_VERSION\0"
    "ISSUER_MISMATCH\0"
    "KEY_TYPE_MISMATCH\0"
    "KEY_VALUES_MISMATCH\0"
    "LOADING_CERT_DIR\0"
    "LOADING_DEFAULTS\0"
    "NAME_TOO_LONG\0"
    "NEWER_CRL_NOT_NEWER\0"
    "NO_CERT_SET_FOR_US_TO_VERIFY\0"
    "NO_CRL_NUMBER\0"
    "PUBLIC_KEY_DECODE_ERROR\0"
    "PUBLIC_KEY_ENCODE_ERROR\0"
    "SHOULD_RETRY\0"
    "SIGNATURE_ALGORITHM_MISMATCH\0"
    "UNKNOWN_KEY_TYPE\0"
    "UNKNOWN_PURPOSE_ID\0"
    "UNKNOWN_TRUST_ID\0"
    "WRONG_LOOKUP_TYPE\0"
    "BAD_IP_ADDRESS\0"
    "BAD_OBJECT\0"
    "BN_DEC2BN_ERROR\0"
    "BN_TO_ASN1_INTEGER_ERROR\0"
    "CANNOT_FIND_FREE_FUNCTION\0"
    "DIRNAME_ERROR\0"
    "DISTPOINT_ALREADY_SET\0"
    "DUPLICATE_ZONE_ID\0"
    "ERROR_CONVERTING_ZONE\0"
    "ERROR_CREATING_EXTENSION\0"
    "ERROR_IN_EXTENSION\0"
    "EXPECTED_A_SECTION_NAME\0"
    "EXTENSION_EXISTS\0"
    "EXTENSION_NAME_ERROR\0"
    "EXTENSION_NOT_FOUND\0"
    "EXTENSION_SETTING_NOT_SUPPORTED\0"
    "EXTENSION_VALUE_ERROR\0"
    "ILLEGAL_EMPTY_EXTENSION\0"
    "ILLEGAL_HEX_DIGIT\0"
    "INCORRECT_POLICY_SYNTAX_TAG\0"
    "INVALID_BOOLEAN_STRING\0"
    "INVALID_EXTENSION_STRING\0"
    "INVALID_MULTIPLE_RDNS\0"
    "INVALID_NAME\0"
    "INVALID_NULL_ARGUMENT\0"
    "INVALID_NULL_NAME\0"
    "INVALID_NULL_VALUE\0"
    "INVALID_NUMBERS\0"
    "INVALID_OBJECT_IDENTIFIER\0"
    "INVALID_OPTION\0"
    "INVALID_POLICY_IDENTIFIER\0"
    "INVALID_PROXY_POLICY_SETTING\0"
    "INVALID_PURPOSE\0"
    "INVALID_SECTION\0"
    "INVALID_SYNTAX\0"
    "ISSUER_DECODE_ERROR\0"
    "NEED_ORGANIZATION_AND_NUMBERS\0"
    "NO_CONFIG_DATABASE\0"
    "NO_ISSUER_CERTIFICATE\0"
    "NO_ISSUER_DETAILS\0"
    "NO_POLICY_IDENTIFIER\0"
    "NO_PROXY_CERT_POLICY_LANGUAGE_DEFINED\0"
    "NO_PUBLIC_KEY\0"
    "NO_SUBJECT_DETAILS\0"
    "ODD_NUMBER_OF_DIGITS\0"
    "OPERATION_NOT_DEFINED\0"
    "OTHERNAME_ERROR\0"
    "POLICY_LANGUAGE_ALREADY_DEFINED\0"
    "POLICY_PATH_LENGTH\0"
    "POLICY_PATH_LENGTH_ALREADY_DEFINED\0"
    "POLICY_WHEN_PROXY_LANGUAGE_REQUIRES_NO_POLICY\0"
    "SECTION_NOT_FOUND\0"
    "UNABLE_TO_GET_ISSUER_DETAILS\0"
    "UNABLE_TO_GET_ISSUER_KEYID\0"
    "UNKNOWN_BIT_STRING_ARGUMENT\0"
    "UNKNOWN_EXTENSION\0"
    "UNKNOWN_EXTENSION_NAME\0"
    "UNKNOWN_OPTION\0"
    "UNSUPPORTED_OPTION\0"
    "USER_TOO_LONG\0"
    "";

