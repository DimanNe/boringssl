/* Copyright (c) 2014, Google Inc.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vector>

#include <gtest/gtest.h>

#include <openssl/bn.h>
#include <openssl/bytestring.h>
#include <openssl/crypto.h>
#include <openssl/ec_key.h>
#include <openssl/err.h>
#include <openssl/mem.h>
#include <openssl/nid.h>
#include <openssl/obj.h>
#include <openssl/span.h>

#include "../../ec_extra/internal.h"
#include "../../test/file_test.h"
#include "../../test/test_util.h"
#include "../bn/internal.h"
#include "internal.h"


// kECKeyWithoutPublic is an ECPrivateKey with the optional publicKey field
// omitted.
static const uint8_t kECKeyWithoutPublic[] = {
  0x30, 0x31, 0x02, 0x01, 0x01, 0x04, 0x20, 0xc6, 0xc1, 0xaa, 0xda, 0x15, 0xb0,
  0x76, 0x61, 0xf8, 0x14, 0x2c, 0x6c, 0xaf, 0x0f, 0xdb, 0x24, 0x1a, 0xff, 0x2e,
  0xfe, 0x46, 0xc0, 0x93, 0x8b, 0x74, 0xf2, 0xbc, 0xc5, 0x30, 0x52, 0xb0, 0x77,
  0xa0, 0x0a, 0x06, 0x08, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x03, 0x01, 0x07,
};

// kECKeySpecifiedCurve is the above key with P-256's parameters explicitly
// spelled out rather than using a named curve.
static const uint8_t kECKeySpecifiedCurve[] = {
    0x30, 0x82, 0x01, 0x22, 0x02, 0x01, 0x01, 0x04, 0x20, 0xc6, 0xc1, 0xaa,
    0xda, 0x15, 0xb0, 0x76, 0x61, 0xf8, 0x14, 0x2c, 0x6c, 0xaf, 0x0f, 0xdb,
    0x24, 0x1a, 0xff, 0x2e, 0xfe, 0x46, 0xc0, 0x93, 0x8b, 0x74, 0xf2, 0xbc,
    0xc5, 0x30, 0x52, 0xb0, 0x77, 0xa0, 0x81, 0xfa, 0x30, 0x81, 0xf7, 0x02,
    0x01, 0x01, 0x30, 0x2c, 0x06, 0x07, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x01,
    0x01, 0x02, 0x21, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x30, 0x5b, 0x04, 0x20, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
    0x04, 0x20, 0x5a, 0xc6, 0x35, 0xd8, 0xaa, 0x3a, 0x93, 0xe7, 0xb3, 0xeb,
    0xbd, 0x55, 0x76, 0x98, 0x86, 0xbc, 0x65, 0x1d, 0x06, 0xb0, 0xcc, 0x53,
    0xb0, 0xf6, 0x3b, 0xce, 0x3c, 0x3e, 0x27, 0xd2, 0x60, 0x4b, 0x03, 0x15,
    0x00, 0xc4, 0x9d, 0x36, 0x08, 0x86, 0xe7, 0x04, 0x93, 0x6a, 0x66, 0x78,
    0xe1, 0x13, 0x9d, 0x26, 0xb7, 0x81, 0x9f, 0x7e, 0x90, 0x04, 0x41, 0x04,
    0x6b, 0x17, 0xd1, 0xf2, 0xe1, 0x2c, 0x42, 0x47, 0xf8, 0xbc, 0xe6, 0xe5,
    0x63, 0xa4, 0x40, 0xf2, 0x77, 0x03, 0x7d, 0x81, 0x2d, 0xeb, 0x33, 0xa0,
    0xf4, 0xa1, 0x39, 0x45, 0xd8, 0x98, 0xc2, 0x96, 0x4f, 0xe3, 0x42, 0xe2,
    0xfe, 0x1a, 0x7f, 0x9b, 0x8e, 0xe7, 0xeb, 0x4a, 0x7c, 0x0f, 0x9e, 0x16,
    0x2b, 0xce, 0x33, 0x57, 0x6b, 0x31, 0x5e, 0xce, 0xcb, 0xb6, 0x40, 0x68,
    0x37, 0xbf, 0x51, 0xf5, 0x02, 0x21, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00,
    0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbc,
    0xe6, 0xfa, 0xad, 0xa7, 0x17, 0x9e, 0x84, 0xf3, 0xb9, 0xca, 0xc2, 0xfc,
    0x63, 0x25, 0x51, 0x02, 0x01, 0x01,
};

// kECKeyMissingZeros is an ECPrivateKey containing a degenerate P-256 key where
// the private key is one. The private key is incorrectly encoded without zero
// padding.
static const uint8_t kECKeyMissingZeros[] = {
  0x30, 0x58, 0x02, 0x01, 0x01, 0x04, 0x01, 0x01, 0xa0, 0x0a, 0x06, 0x08, 0x2a,
  0x86, 0x48, 0xce, 0x3d, 0x03, 0x01, 0x07, 0xa1, 0x44, 0x03, 0x42, 0x00, 0x04,
  0x6b, 0x17, 0xd1, 0xf2, 0xe1, 0x2c, 0x42, 0x47, 0xf8, 0xbc, 0xe6, 0xe5, 0x63,
  0xa4, 0x40, 0xf2, 0x77, 0x03, 0x7d, 0x81, 0x2d, 0xeb, 0x33, 0xa0, 0xf4, 0xa1,
  0x39, 0x45, 0xd8, 0x98, 0xc2, 0x96, 0x4f, 0xe3, 0x42, 0xe2, 0xfe, 0x1a, 0x7f,
  0x9b, 0x8e, 0xe7, 0xeb, 0x4a, 0x7c, 0x0f, 0x9e, 0x16, 0x2b, 0xce, 0x33, 0x57,
  0x6b, 0x31, 0x5e, 0xce, 0xcb, 0xb6, 0x40, 0x68, 0x37, 0xbf, 0x51, 0xf5,
};

// kECKeyMissingZeros is an ECPrivateKey containing a degenerate P-256 key where
// the private key is one. The private key is encoded with the required zero
// padding.
static const uint8_t kECKeyWithZeros[] = {
  0x30, 0x77, 0x02, 0x01, 0x01, 0x04, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0xa0, 0x0a, 0x06, 0x08, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x03, 0x01, 0x07, 0xa1,
  0x44, 0x03, 0x42, 0x00, 0x04, 0x6b, 0x17, 0xd1, 0xf2, 0xe1, 0x2c, 0x42, 0x47,
  0xf8, 0xbc, 0xe6, 0xe5, 0x63, 0xa4, 0x40, 0xf2, 0x77, 0x03, 0x7d, 0x81, 0x2d,
  0xeb, 0x33, 0xa0, 0xf4, 0xa1, 0x39, 0x45, 0xd8, 0x98, 0xc2, 0x96, 0x4f, 0xe3,
  0x42, 0xe2, 0xfe, 0x1a, 0x7f, 0x9b, 0x8e, 0xe7, 0xeb, 0x4a, 0x7c, 0x0f, 0x9e,
  0x16, 0x2b, 0xce, 0x33, 0x57, 0x6b, 0x31, 0x5e, 0xce, 0xcb, 0xb6, 0x40, 0x68,
  0x37, 0xbf, 0x51, 0xf5,
};

// DecodeECPrivateKey decodes |in| as an ECPrivateKey structure and returns the
// result or nullptr on error.
static bssl::UniquePtr<EC_KEY> DecodeECPrivateKey(const uint8_t *in,
                                                  size_t in_len) {
  CBS cbs;
  CBS_init(&cbs, in, in_len);
  bssl::UniquePtr<EC_KEY> ret(EC_KEY_parse_private_key(&cbs, NULL));
  if (!ret || CBS_len(&cbs) != 0) {
    return nullptr;
  }
  return ret;
}

// EncodeECPrivateKey encodes |key| as an ECPrivateKey structure into |*out|. It
// returns true on success or false on error.
static bool EncodeECPrivateKey(std::vector<uint8_t> *out, const EC_KEY *key) {
  bssl::ScopedCBB cbb;
  uint8_t *der;
  size_t der_len;
  if (!CBB_init(cbb.get(), 0) ||
      !EC_KEY_marshal_private_key(cbb.get(), key, EC_KEY_get_enc_flags(key)) ||
      !CBB_finish(cbb.get(), &der, &der_len)) {
    return false;
  }
  out->assign(der, der + der_len);
  OPENSSL_free(der);
  return true;
}

static bool EncodeECPoint(std::vector<uint8_t> *out, const EC_GROUP *group,
                          const EC_POINT *p, point_conversion_form_t form) {
  size_t len = EC_POINT_point2oct(group, p, form, nullptr, 0, nullptr);
  if (len == 0) {
    return false;
  }

  out->resize(len);
  len = EC_POINT_point2oct(group, p, form, out->data(), out->size(), nullptr);
  if (len != out->size()) {
    return false;
  }

  return true;
}

TEST(ECTest, Encoding) {
  bssl::UniquePtr<EC_KEY> key =
      DecodeECPrivateKey(kECKeyWithoutPublic, sizeof(kECKeyWithoutPublic));
  ASSERT_TRUE(key);

  // Test that the encoding round-trips.
  std::vector<uint8_t> out;
  ASSERT_TRUE(EncodeECPrivateKey(&out, key.get()));
  EXPECT_EQ(Bytes(kECKeyWithoutPublic), Bytes(out.data(), out.size()));

  const EC_POINT *pub_key = EC_KEY_get0_public_key(key.get());
  ASSERT_TRUE(pub_key) << "Public key missing";

  bssl::UniquePtr<BIGNUM> x(BN_new());
  bssl::UniquePtr<BIGNUM> y(BN_new());
  ASSERT_TRUE(x);
  ASSERT_TRUE(y);
  ASSERT_TRUE(EC_POINT_get_affine_coordinates_GFp(
      EC_KEY_get0_group(key.get()), pub_key, x.get(), y.get(), NULL));
  bssl::UniquePtr<char> x_hex(BN_bn2hex(x.get()));
  bssl::UniquePtr<char> y_hex(BN_bn2hex(y.get()));
  ASSERT_TRUE(x_hex);
  ASSERT_TRUE(y_hex);

  EXPECT_STREQ(
      "c81561ecf2e54edefe6617db1c7a34a70744ddb261f269b83dacfcd2ade5a681",
      x_hex.get());
  EXPECT_STREQ(
      "e0e2afa3f9b6abe4c698ef6495f1be49a3196c5056acb3763fe4507eec596e88",
      y_hex.get());
}

TEST(ECTest, ZeroPadding) {
  // Check that the correct encoding round-trips.
  bssl::UniquePtr<EC_KEY> key =
      DecodeECPrivateKey(kECKeyWithZeros, sizeof(kECKeyWithZeros));
  ASSERT_TRUE(key);
  std::vector<uint8_t> out;
  EXPECT_TRUE(EncodeECPrivateKey(&out, key.get()));
  EXPECT_EQ(Bytes(kECKeyWithZeros), Bytes(out.data(), out.size()));

  // Keys without leading zeros also parse, but they encode correctly.
  key = DecodeECPrivateKey(kECKeyMissingZeros, sizeof(kECKeyMissingZeros));
  ASSERT_TRUE(key);
  EXPECT_TRUE(EncodeECPrivateKey(&out, key.get()));
  EXPECT_EQ(Bytes(kECKeyWithZeros), Bytes(out.data(), out.size()));
}

TEST(ECTest, SpecifiedCurve) {
  // Test keys with specified curves may be decoded.
  bssl::UniquePtr<EC_KEY> key =
      DecodeECPrivateKey(kECKeySpecifiedCurve, sizeof(kECKeySpecifiedCurve));
  ASSERT_TRUE(key);

  // The group should have been interpreted as P-256.
  EXPECT_EQ(NID_X9_62_prime256v1,
            EC_GROUP_get_curve_name(EC_KEY_get0_group(key.get())));

  // Encoding the key should still use named form.
  std::vector<uint8_t> out;
  EXPECT_TRUE(EncodeECPrivateKey(&out, key.get()));
  EXPECT_EQ(Bytes(kECKeyWithoutPublic), Bytes(out.data(), out.size()));
}

TEST(ECTest, ArbitraryCurve) {
  // Make a P-256 key and extract the affine coordinates.
  bssl::UniquePtr<EC_KEY> key(EC_KEY_new_by_curve_name(NID_X9_62_prime256v1));
  ASSERT_TRUE(key);
  ASSERT_TRUE(EC_KEY_generate_key(key.get()));

  // Make an arbitrary curve which is identical to P-256.
  static const uint8_t kP[] = {
      0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  };
  static const uint8_t kA[] = {
      0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
  };
  static const uint8_t kB[] = {
      0x5a, 0xc6, 0x35, 0xd8, 0xaa, 0x3a, 0x93, 0xe7, 0xb3, 0xeb, 0xbd,
      0x55, 0x76, 0x98, 0x86, 0xbc, 0x65, 0x1d, 0x06, 0xb0, 0xcc, 0x53,
      0xb0, 0xf6, 0x3b, 0xce, 0x3c, 0x3e, 0x27, 0xd2, 0x60, 0x4b,
  };
  static const uint8_t kX[] = {
      0x6b, 0x17, 0xd1, 0xf2, 0xe1, 0x2c, 0x42, 0x47, 0xf8, 0xbc, 0xe6,
      0xe5, 0x63, 0xa4, 0x40, 0xf2, 0x77, 0x03, 0x7d, 0x81, 0x2d, 0xeb,
      0x33, 0xa0, 0xf4, 0xa1, 0x39, 0x45, 0xd8, 0x98, 0xc2, 0x96,
  };
  static const uint8_t kY[] = {
      0x4f, 0xe3, 0x42, 0xe2, 0xfe, 0x1a, 0x7f, 0x9b, 0x8e, 0xe7, 0xeb,
      0x4a, 0x7c, 0x0f, 0x9e, 0x16, 0x2b, 0xce, 0x33, 0x57, 0x6b, 0x31,
      0x5e, 0xce, 0xcb, 0xb6, 0x40, 0x68, 0x37, 0xbf, 0x51, 0xf5,
  };
  static const uint8_t kOrder[] = {
      0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xbc, 0xe6, 0xfa, 0xad, 0xa7, 0x17,
      0x9e, 0x84, 0xf3, 0xb9, 0xca, 0xc2, 0xfc, 0x63, 0x25, 0x51,
  };
  bssl::UniquePtr<BN_CTX> ctx(BN_CTX_new());
  ASSERT_TRUE(ctx);
  bssl::UniquePtr<BIGNUM> p(BN_bin2bn(kP, sizeof(kP), nullptr));
  ASSERT_TRUE(p);
  bssl::UniquePtr<BIGNUM> a(BN_bin2bn(kA, sizeof(kA), nullptr));
  ASSERT_TRUE(a);
  bssl::UniquePtr<BIGNUM> b(BN_bin2bn(kB, sizeof(kB), nullptr));
  ASSERT_TRUE(b);
  bssl::UniquePtr<BIGNUM> gx(BN_bin2bn(kX, sizeof(kX), nullptr));
  ASSERT_TRUE(gx);
  bssl::UniquePtr<BIGNUM> gy(BN_bin2bn(kY, sizeof(kY), nullptr));
  ASSERT_TRUE(gy);
  bssl::UniquePtr<BIGNUM> order(BN_bin2bn(kOrder, sizeof(kOrder), nullptr));
  ASSERT_TRUE(order);

  bssl::UniquePtr<EC_GROUP> group(
      EC_GROUP_new_curve_GFp(p.get(), a.get(), b.get(), ctx.get()));
  ASSERT_TRUE(group);
  bssl::UniquePtr<EC_POINT> generator(EC_POINT_new(group.get()));
  ASSERT_TRUE(generator);
  ASSERT_TRUE(EC_POINT_set_affine_coordinates_GFp(
      group.get(), generator.get(), gx.get(), gy.get(), ctx.get()));
  ASSERT_TRUE(EC_GROUP_set_generator(group.get(), generator.get(), order.get(),
                                     BN_value_one()));

  // |group| should not have a curve name.
  EXPECT_EQ(NID_undef, EC_GROUP_get_curve_name(group.get()));

  // Copy |key| to |key2| using |group|.
  bssl::UniquePtr<EC_KEY> key2(EC_KEY_new());
  ASSERT_TRUE(key2);
  bssl::UniquePtr<EC_POINT> point(EC_POINT_new(group.get()));
  ASSERT_TRUE(point);
  bssl::UniquePtr<BIGNUM> x(BN_new()), y(BN_new());
  ASSERT_TRUE(x);
  ASSERT_TRUE(EC_KEY_set_group(key2.get(), group.get()));
  ASSERT_TRUE(
      EC_KEY_set_private_key(key2.get(), EC_KEY_get0_private_key(key.get())));
  ASSERT_TRUE(EC_POINT_get_affine_coordinates_GFp(
      EC_KEY_get0_group(key.get()), EC_KEY_get0_public_key(key.get()), x.get(),
      y.get(), nullptr));
  ASSERT_TRUE(EC_POINT_set_affine_coordinates_GFp(group.get(), point.get(),
                                                  x.get(), y.get(), nullptr));
  ASSERT_TRUE(EC_KEY_set_public_key(key2.get(), point.get()));

  // The key must be valid according to the new group too.
  EXPECT_TRUE(EC_KEY_check_key(key2.get()));

  // Make a second instance of |group|.
  bssl::UniquePtr<EC_GROUP> group2(
      EC_GROUP_new_curve_GFp(p.get(), a.get(), b.get(), ctx.get()));
  ASSERT_TRUE(group2);
  bssl::UniquePtr<EC_POINT> generator2(EC_POINT_new(group2.get()));
  ASSERT_TRUE(generator2);
  ASSERT_TRUE(EC_POINT_set_affine_coordinates_GFp(
      group2.get(), generator2.get(), gx.get(), gy.get(), ctx.get()));
  ASSERT_TRUE(EC_GROUP_set_generator(group2.get(), generator2.get(),
                                     order.get(), BN_value_one()));

  EXPECT_EQ(0, EC_GROUP_cmp(group.get(), group.get(), NULL));
  EXPECT_EQ(0, EC_GROUP_cmp(group2.get(), group.get(), NULL));

  // group3 uses the wrong generator.
  bssl::UniquePtr<EC_GROUP> group3(
      EC_GROUP_new_curve_GFp(p.get(), a.get(), b.get(), ctx.get()));
  ASSERT_TRUE(group3);
  bssl::UniquePtr<EC_POINT> generator3(EC_POINT_new(group3.get()));
  ASSERT_TRUE(generator3);
  ASSERT_TRUE(EC_POINT_set_affine_coordinates_GFp(
      group3.get(), generator3.get(), x.get(), y.get(), ctx.get()));
  ASSERT_TRUE(EC_GROUP_set_generator(group3.get(), generator3.get(),
                                     order.get(), BN_value_one()));

  EXPECT_NE(0, EC_GROUP_cmp(group.get(), group3.get(), NULL));

#if !defined(BORINGSSL_SHARED_LIBRARY)
  // group4 has non-minimal components that do not fit in |EC_SCALAR| and the
  // future |EC_FELEM|.
  ASSERT_TRUE(bn_resize_words(p.get(), 32));
  ASSERT_TRUE(bn_resize_words(a.get(), 32));
  ASSERT_TRUE(bn_resize_words(b.get(), 32));
  ASSERT_TRUE(bn_resize_words(gx.get(), 32));
  ASSERT_TRUE(bn_resize_words(gy.get(), 32));
  ASSERT_TRUE(bn_resize_words(order.get(), 32));

  bssl::UniquePtr<EC_GROUP> group4(
      EC_GROUP_new_curve_GFp(p.get(), a.get(), b.get(), ctx.get()));
  ASSERT_TRUE(group4);
  bssl::UniquePtr<EC_POINT> generator4(EC_POINT_new(group4.get()));
  ASSERT_TRUE(generator4);
  ASSERT_TRUE(EC_POINT_set_affine_coordinates_GFp(
      group4.get(), generator4.get(), gx.get(), gy.get(), ctx.get()));
  ASSERT_TRUE(EC_GROUP_set_generator(group4.get(), generator4.get(),
                                     order.get(), BN_value_one()));

  EXPECT_EQ(0, EC_GROUP_cmp(group.get(), group4.get(), NULL));
#endif

  // group5 is the same group, but the curve coefficients are passed in
  // unreduced and the caller does not pass in a |BN_CTX|.
  ASSERT_TRUE(BN_sub(a.get(), a.get(), p.get()));
  ASSERT_TRUE(BN_add(b.get(), b.get(), p.get()));
  bssl::UniquePtr<EC_GROUP> group5(
      EC_GROUP_new_curve_GFp(p.get(), a.get(), b.get(), NULL));
  ASSERT_TRUE(group5);
  bssl::UniquePtr<EC_POINT> generator5(EC_POINT_new(group5.get()));
  ASSERT_TRUE(generator5);
  ASSERT_TRUE(EC_POINT_set_affine_coordinates_GFp(
      group5.get(), generator5.get(), gx.get(), gy.get(), ctx.get()));
  ASSERT_TRUE(EC_GROUP_set_generator(group5.get(), generator5.get(),
                                     order.get(), BN_value_one()));

  EXPECT_EQ(0, EC_GROUP_cmp(group.get(), group.get(), NULL));
  EXPECT_EQ(0, EC_GROUP_cmp(group5.get(), group.get(), NULL));
}

TEST(ECTest, SetKeyWithoutGroup) {
  bssl::UniquePtr<EC_KEY> key(EC_KEY_new());
  ASSERT_TRUE(key);

  // Private keys may not be configured without a group.
  EXPECT_FALSE(EC_KEY_set_private_key(key.get(), BN_value_one()));

  // Public keys may not be configured without a group.
  bssl::UniquePtr<EC_GROUP> group(
      EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1));
  ASSERT_TRUE(group);
  EXPECT_FALSE(
      EC_KEY_set_public_key(key.get(), EC_GROUP_get0_generator(group.get())));
}

TEST(ECTest, SetNULLKey) {
  bssl::UniquePtr<EC_KEY> key(EC_KEY_new_by_curve_name(NID_X9_62_prime256v1));
  ASSERT_TRUE(key);

  EXPECT_TRUE(EC_KEY_set_public_key(
      key.get(), EC_GROUP_get0_generator(EC_KEY_get0_group(key.get()))));
  EXPECT_TRUE(EC_KEY_get0_public_key(key.get()));

  // Setting a NULL public-key should clear the public-key and return zero, in
  // order to match OpenSSL behaviour exactly.
  EXPECT_FALSE(EC_KEY_set_public_key(key.get(), nullptr));
  EXPECT_FALSE(EC_KEY_get0_public_key(key.get()));
}

TEST(ECTest, GroupMismatch) {
  bssl::UniquePtr<EC_KEY> key(EC_KEY_new_by_curve_name(NID_secp384r1));
  ASSERT_TRUE(key);
  bssl::UniquePtr<EC_GROUP> p256(
      EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1));
  ASSERT_TRUE(p256);

  // Changing a key's group is invalid.
  EXPECT_FALSE(EC_KEY_set_group(key.get(), p256.get()));

  // Configuring a public key with the wrong group is invalid.
  EXPECT_FALSE(
      EC_KEY_set_public_key(key.get(), EC_GROUP_get0_generator(p256.get())));
}

TEST(ECTest, EmptyKey) {
  bssl::UniquePtr<EC_KEY> key(EC_KEY_new());
  ASSERT_TRUE(key);
  EXPECT_FALSE(EC_KEY_get0_group(key.get()));
  EXPECT_FALSE(EC_KEY_get0_public_key(key.get()));
  EXPECT_FALSE(EC_KEY_get0_private_key(key.get()));
}

static bssl::UniquePtr<BIGNUM> HexToBIGNUM(const char *hex) {
  BIGNUM *bn = nullptr;
  BN_hex2bn(&bn, hex);
  return bssl::UniquePtr<BIGNUM>(bn);
}

// Test that point arithmetic works with custom curves using an arbitrary |a|,
// rather than -3, as is common (and more efficient).
TEST(ECTest, BrainpoolP256r1) {
  static const char kP[] =
      "a9fb57dba1eea9bc3e660a909d838d726e3bf623d52620282013481d1f6e5377";
  static const char kA[] =
      "7d5a0975fc2c3057eef67530417affe7fb8055c126dc5c6ce94a4b44f330b5d9";
  static const char kB[] =
      "26dc5c6ce94a4b44f330b5d9bbd77cbf958416295cf7e1ce6bccdc18ff8c07b6";
  static const char kX[] =
      "8bd2aeb9cb7e57cb2c4b482ffc81b7afb9de27e1e3bd23c23a4453bd9ace3262";
  static const char kY[] =
      "547ef835c3dac4fd97f8461a14611dc9c27745132ded8e545c1d54c72f046997";
  static const char kN[] =
      "a9fb57dba1eea9bc3e660a909d838d718c397aa3b561a6f7901e0e82974856a7";
  static const char kD[] =
      "0da21d76fed40dd82ac3314cce91abb585b5c4246e902b238a839609ea1e7ce1";
  static const char kQX[] =
      "3a55e0341cab50452fe27b8a87e4775dec7a9daca94b0d84ad1e9f85b53ea513";
  static const char kQY[] =
      "40088146b33bbbe81b092b41146774b35dd478cf056437cfb35ef0df2d269339";

  bssl::UniquePtr<BIGNUM> p = HexToBIGNUM(kP), a = HexToBIGNUM(kA),
                          b = HexToBIGNUM(kB), x = HexToBIGNUM(kX),
                          y = HexToBIGNUM(kY), n = HexToBIGNUM(kN),
                          d = HexToBIGNUM(kD), qx = HexToBIGNUM(kQX),
                          qy = HexToBIGNUM(kQY);
  ASSERT_TRUE(p && a && b && x && y && n && d && qx && qy);

  bssl::UniquePtr<EC_GROUP> group(
      EC_GROUP_new_curve_GFp(p.get(), a.get(), b.get(), nullptr));
  ASSERT_TRUE(group);
  bssl::UniquePtr<EC_POINT> g(EC_POINT_new(group.get()));
  ASSERT_TRUE(g);
  ASSERT_TRUE(EC_POINT_set_affine_coordinates_GFp(group.get(), g.get(), x.get(),
                                                  y.get(), nullptr));
  ASSERT_TRUE(
      EC_GROUP_set_generator(group.get(), g.get(), n.get(), BN_value_one()));

  bssl::UniquePtr<EC_POINT> q(EC_POINT_new(group.get()));
  ASSERT_TRUE(q);
  ASSERT_TRUE(
      EC_POINT_mul(group.get(), q.get(), d.get(), nullptr, nullptr, nullptr));
  ASSERT_TRUE(EC_POINT_get_affine_coordinates_GFp(group.get(), q.get(), x.get(),
                                                  y.get(), nullptr));
  EXPECT_EQ(0, BN_cmp(x.get(), qx.get()));
  EXPECT_EQ(0, BN_cmp(y.get(), qy.get()));
}

class ECCurveTest : public testing::TestWithParam<EC_builtin_curve> {
 public:
  const EC_GROUP *group() const { return group_.get(); }

  void SetUp() override {
    group_.reset(EC_GROUP_new_by_curve_name(GetParam().nid));
    ASSERT_TRUE(group_);
  }

 private:
  bssl::UniquePtr<EC_GROUP> group_;
};

TEST_P(ECCurveTest, SetAffine) {
  // Generate an EC_KEY.
  bssl::UniquePtr<EC_KEY> key(EC_KEY_new_by_curve_name(GetParam().nid));
  ASSERT_TRUE(key);
  ASSERT_TRUE(EC_KEY_generate_key(key.get()));

  // Get the public key's coordinates.
  bssl::UniquePtr<BIGNUM> x(BN_new());
  ASSERT_TRUE(x);
  bssl::UniquePtr<BIGNUM> y(BN_new());
  ASSERT_TRUE(y);
  bssl::UniquePtr<BIGNUM> p(BN_new());
  ASSERT_TRUE(p);
  EXPECT_TRUE(EC_POINT_get_affine_coordinates_GFp(
      group(), EC_KEY_get0_public_key(key.get()), x.get(), y.get(), nullptr));
  EXPECT_TRUE(
      EC_GROUP_get_curve_GFp(group(), p.get(), nullptr, nullptr, nullptr));

  // Points on the curve should be accepted.
  auto point = bssl::UniquePtr<EC_POINT>(EC_POINT_new(group()));
  ASSERT_TRUE(point);
  EXPECT_TRUE(EC_POINT_set_affine_coordinates_GFp(group(), point.get(), x.get(),
                                                  y.get(), nullptr));

  // Subtract one from |y| to make the point no longer on the curve.
  EXPECT_TRUE(BN_sub(y.get(), y.get(), BN_value_one()));

  // Points not on the curve should be rejected.
  bssl::UniquePtr<EC_POINT> invalid_point(EC_POINT_new(group()));
  ASSERT_TRUE(invalid_point);
  EXPECT_FALSE(EC_POINT_set_affine_coordinates_GFp(group(), invalid_point.get(),
                                                   x.get(), y.get(), nullptr));

  // Coordinates out of range should be rejected.
  EXPECT_TRUE(BN_add(y.get(), y.get(), BN_value_one()));
  EXPECT_TRUE(BN_add(y.get(), y.get(), p.get()));

  EXPECT_FALSE(EC_POINT_set_affine_coordinates_GFp(group(), invalid_point.get(),
                                                   x.get(), y.get(), nullptr));
  EXPECT_FALSE(
      EC_KEY_set_public_key_affine_coordinates(key.get(), x.get(), y.get()));
}

TEST_P(ECCurveTest, IsOnCurve) {
  bssl::UniquePtr<EC_KEY> key(EC_KEY_new_by_curve_name(GetParam().nid));
  ASSERT_TRUE(key);
  ASSERT_TRUE(EC_KEY_generate_key(key.get()));

  // The generated point is on the curve.
  EXPECT_TRUE(EC_POINT_is_on_curve(group(), EC_KEY_get0_public_key(key.get()),
                                   nullptr));

  bssl::UniquePtr<EC_POINT> p(EC_POINT_new(group()));
  ASSERT_TRUE(p);
  ASSERT_TRUE(EC_POINT_copy(p.get(), EC_KEY_get0_public_key(key.get())));

  // This should never happen outside of a bug, but |EC_POINT_is_on_curve|
  // rejects points not on the curve.
  OPENSSL_memset(&p->raw.X, 0, sizeof(p->raw.X));
  EXPECT_FALSE(EC_POINT_is_on_curve(group(), p.get(), nullptr));

  // The point at infinity is always on the curve.
  ASSERT_TRUE(EC_POINT_copy(p.get(), EC_KEY_get0_public_key(key.get())));
  OPENSSL_memset(&p->raw.Z, 0, sizeof(p->raw.Z));
  EXPECT_TRUE(EC_POINT_is_on_curve(group(), p.get(), nullptr));
}

TEST_P(ECCurveTest, GenerateFIPS) {
  // Generate an EC_KEY.
  bssl::UniquePtr<EC_KEY> key(EC_KEY_new_by_curve_name(GetParam().nid));
  ASSERT_TRUE(key);
  ASSERT_TRUE(EC_KEY_generate_key_fips(key.get()));
}

TEST_P(ECCurveTest, AddingEqualPoints) {
  bssl::UniquePtr<EC_KEY> key(EC_KEY_new_by_curve_name(GetParam().nid));
  ASSERT_TRUE(key);
  ASSERT_TRUE(EC_KEY_generate_key(key.get()));

  bssl::UniquePtr<EC_POINT> p1(EC_POINT_new(group()));
  ASSERT_TRUE(p1);
  ASSERT_TRUE(EC_POINT_copy(p1.get(), EC_KEY_get0_public_key(key.get())));

  bssl::UniquePtr<EC_POINT> p2(EC_POINT_new(group()));
  ASSERT_TRUE(p2);
  ASSERT_TRUE(EC_POINT_copy(p2.get(), EC_KEY_get0_public_key(key.get())));

  bssl::UniquePtr<EC_POINT> double_p1(EC_POINT_new(group()));
  ASSERT_TRUE(double_p1);
  bssl::UniquePtr<BN_CTX> ctx(BN_CTX_new());
  ASSERT_TRUE(ctx);
  ASSERT_TRUE(EC_POINT_dbl(group(), double_p1.get(), p1.get(), ctx.get()));

  bssl::UniquePtr<EC_POINT> p1_plus_p2(EC_POINT_new(group()));
  ASSERT_TRUE(p1_plus_p2);
  ASSERT_TRUE(
      EC_POINT_add(group(), p1_plus_p2.get(), p1.get(), p2.get(), ctx.get()));

  EXPECT_EQ(0,
            EC_POINT_cmp(group(), double_p1.get(), p1_plus_p2.get(), ctx.get()))
      << "A+A != 2A";
}

TEST_P(ECCurveTest, MulZero) {
  bssl::UniquePtr<EC_POINT> point(EC_POINT_new(group()));
  ASSERT_TRUE(point);
  bssl::UniquePtr<BIGNUM> zero(BN_new());
  ASSERT_TRUE(zero);
  BN_zero(zero.get());
  ASSERT_TRUE(EC_POINT_mul(group(), point.get(), zero.get(), nullptr, nullptr,
                           nullptr));

  EXPECT_TRUE(EC_POINT_is_at_infinity(group(), point.get()))
      << "g * 0 did not return point at infinity.";

  // Test that zero times an arbitrary point is also infinity. The generator is
  // used as the arbitrary point.
  bssl::UniquePtr<EC_POINT> generator(EC_POINT_new(group()));
  ASSERT_TRUE(generator);
  ASSERT_TRUE(EC_POINT_mul(group(), generator.get(), BN_value_one(), nullptr,
                           nullptr, nullptr));
  ASSERT_TRUE(EC_POINT_mul(group(), point.get(), nullptr, generator.get(),
                           zero.get(), nullptr));

  EXPECT_TRUE(EC_POINT_is_at_infinity(group(), point.get()))
      << "p * 0 did not return point at infinity.";
}

// Test that multiplying by the order produces ∞ and, moreover, that callers may
// do so. |EC_POINT_mul| is almost exclusively used with reduced scalars, with
// this exception. This comes from consumers following NIST SP 800-56A section
// 5.6.2.3.2. (Though all our curves have cofactor one, so this check isn't
// useful.)
TEST_P(ECCurveTest, MulOrder) {
  // Test that g × order = ∞.
  bssl::UniquePtr<EC_POINT> point(EC_POINT_new(group()));
  ASSERT_TRUE(point);
  ASSERT_TRUE(EC_POINT_mul(group(), point.get(), EC_GROUP_get0_order(group()),
                           nullptr, nullptr, nullptr));

  EXPECT_TRUE(EC_POINT_is_at_infinity(group(), point.get()))
      << "g * order did not return point at infinity.";

  // Test that p × order = ∞, for some arbitrary p.
  bssl::UniquePtr<BIGNUM> forty_two(BN_new());
  ASSERT_TRUE(forty_two);
  ASSERT_TRUE(BN_set_word(forty_two.get(), 42));
  ASSERT_TRUE(EC_POINT_mul(group(), point.get(), forty_two.get(), nullptr,
                           nullptr, nullptr));
  ASSERT_TRUE(EC_POINT_mul(group(), point.get(), nullptr, point.get(),
                           EC_GROUP_get0_order(group()), nullptr));

  EXPECT_TRUE(EC_POINT_is_at_infinity(group(), point.get()))
      << "p * order did not return point at infinity.";
}

// Test that |EC_POINT_mul| works with out-of-range scalars. The operation will
// not be constant-time, but we'll compute the right answer.
TEST_P(ECCurveTest, MulOutOfRange) {
  bssl::UniquePtr<BIGNUM> n_minus_one(BN_dup(EC_GROUP_get0_order(group())));
  ASSERT_TRUE(n_minus_one);
  ASSERT_TRUE(BN_sub_word(n_minus_one.get(), 1));

  bssl::UniquePtr<BIGNUM> minus_one(BN_new());
  ASSERT_TRUE(minus_one);
  ASSERT_TRUE(BN_one(minus_one.get()));
  BN_set_negative(minus_one.get(), 1);

  bssl::UniquePtr<BIGNUM> seven(BN_new());
  ASSERT_TRUE(seven);
  ASSERT_TRUE(BN_set_word(seven.get(), 7));

  bssl::UniquePtr<BIGNUM> ten_n_plus_seven(
      BN_dup(EC_GROUP_get0_order(group())));
  ASSERT_TRUE(ten_n_plus_seven);
  ASSERT_TRUE(BN_mul_word(ten_n_plus_seven.get(), 10));
  ASSERT_TRUE(BN_add_word(ten_n_plus_seven.get(), 7));

  bssl::UniquePtr<EC_POINT> point1(EC_POINT_new(group())),
      point2(EC_POINT_new(group()));
  ASSERT_TRUE(point1);
  ASSERT_TRUE(point2);

  ASSERT_TRUE(EC_POINT_mul(group(), point1.get(), n_minus_one.get(), nullptr,
                           nullptr, nullptr));
  ASSERT_TRUE(EC_POINT_mul(group(), point2.get(), minus_one.get(), nullptr,
                           nullptr, nullptr));
  EXPECT_EQ(0, EC_POINT_cmp(group(), point1.get(), point2.get(), nullptr))
      << "-1 * G and (n-1) * G did not give the same result";

  ASSERT_TRUE(EC_POINT_mul(group(), point1.get(), seven.get(), nullptr, nullptr,
                           nullptr));
  ASSERT_TRUE(EC_POINT_mul(group(), point2.get(), ten_n_plus_seven.get(),
                           nullptr, nullptr, nullptr));
  EXPECT_EQ(0, EC_POINT_cmp(group(), point1.get(), point2.get(), nullptr))
      << "7 * G and (10n + 7) * G did not give the same result";
}

// Test that 10×∞ + G = G.
TEST_P(ECCurveTest, Mul) {
  bssl::UniquePtr<EC_POINT> p(EC_POINT_new(group()));
  ASSERT_TRUE(p);
  bssl::UniquePtr<EC_POINT> result(EC_POINT_new(group()));
  ASSERT_TRUE(result);
  bssl::UniquePtr<BIGNUM> n(BN_new());
  ASSERT_TRUE(n);
  ASSERT_TRUE(EC_POINT_set_to_infinity(group(), p.get()));
  ASSERT_TRUE(BN_set_word(n.get(), 10));

  // First check that 10×∞ = ∞.
  ASSERT_TRUE(
      EC_POINT_mul(group(), result.get(), nullptr, p.get(), n.get(), nullptr));
  EXPECT_TRUE(EC_POINT_is_at_infinity(group(), result.get()));

  // Now check that 10×∞ + G = G.
  const EC_POINT *generator = EC_GROUP_get0_generator(group());
  ASSERT_TRUE(EC_POINT_mul(group(), result.get(), BN_value_one(), p.get(),
                           n.get(), nullptr));
  EXPECT_EQ(0, EC_POINT_cmp(group(), result.get(), generator, nullptr));
}

TEST_P(ECCurveTest, MulNonMinimal) {
  bssl::UniquePtr<BIGNUM> forty_two(BN_new());
  ASSERT_TRUE(forty_two);
  ASSERT_TRUE(BN_set_word(forty_two.get(), 42));

  // Compute g × 42.
  bssl::UniquePtr<EC_POINT> point(EC_POINT_new(group()));
  ASSERT_TRUE(point);
  ASSERT_TRUE(EC_POINT_mul(group(), point.get(), forty_two.get(), nullptr,
                           nullptr, nullptr));

  // Compute it again with a non-minimal 42, much larger than the scalar.
  ASSERT_TRUE(bn_resize_words(forty_two.get(), 64));

  bssl::UniquePtr<EC_POINT> point2(EC_POINT_new(group()));
  ASSERT_TRUE(point2);
  ASSERT_TRUE(EC_POINT_mul(group(), point2.get(), forty_two.get(), nullptr,
                           nullptr, nullptr));
  EXPECT_EQ(0, EC_POINT_cmp(group(), point.get(), point2.get(), nullptr));
}

// Test that EC_KEY_set_private_key rejects invalid values.
TEST_P(ECCurveTest, SetInvalidPrivateKey) {
  bssl::UniquePtr<EC_KEY> key(EC_KEY_new_by_curve_name(GetParam().nid));
  ASSERT_TRUE(key);

  bssl::UniquePtr<BIGNUM> bn(BN_new());
  ASSERT_TRUE(BN_one(bn.get()));
  BN_set_negative(bn.get(), 1);
  EXPECT_FALSE(EC_KEY_set_private_key(key.get(), bn.get()))
      << "Unexpectedly set a key of -1";
  ERR_clear_error();

  ASSERT_TRUE(
      BN_copy(bn.get(), EC_GROUP_get0_order(EC_KEY_get0_group(key.get()))));
  EXPECT_FALSE(EC_KEY_set_private_key(key.get(), bn.get()))
      << "Unexpectedly set a key of the group order.";
  ERR_clear_error();
}

TEST_P(ECCurveTest, IgnoreOct2PointReturnValue) {
  bssl::UniquePtr<BIGNUM> forty_two(BN_new());
  ASSERT_TRUE(forty_two);
  ASSERT_TRUE(BN_set_word(forty_two.get(), 42));

  // Compute g × 42.
  bssl::UniquePtr<EC_POINT> point(EC_POINT_new(group()));
  ASSERT_TRUE(point);
  ASSERT_TRUE(EC_POINT_mul(group(), point.get(), forty_two.get(), nullptr,
                           nullptr, nullptr));

  // Serialize the point.
  std::vector<uint8_t> serialized;
  ASSERT_TRUE(EncodeECPoint(&serialized, group(), point.get(),
                            POINT_CONVERSION_UNCOMPRESSED));

  // Create a serialized point that is not on the curve.
  serialized[serialized.size() - 1]++;

  ASSERT_FALSE(EC_POINT_oct2point(group(), point.get(), serialized.data(),
                                  serialized.size(), nullptr));
  // After a failure, |point| should have been set to the generator to defend
  // against code that doesn't check the return value.
  ASSERT_EQ(0, EC_POINT_cmp(group(), point.get(),
                            EC_GROUP_get0_generator(group()), nullptr));
}

TEST_P(ECCurveTest, DoubleSpecialCase) {
  const EC_POINT *g = EC_GROUP_get0_generator(group());

  bssl::UniquePtr<EC_POINT> two_g(EC_POINT_new(group()));
  ASSERT_TRUE(two_g);
  ASSERT_TRUE(EC_POINT_dbl(group(), two_g.get(), g, nullptr));

  bssl::UniquePtr<EC_POINT> p(EC_POINT_new(group()));
  ASSERT_TRUE(p);
  ASSERT_TRUE(EC_POINT_mul(group(), p.get(), BN_value_one(), g, BN_value_one(),
                           nullptr));
  EXPECT_EQ(0, EC_POINT_cmp(group(), p.get(), two_g.get(), nullptr));

  EC_SCALAR one;
  ASSERT_TRUE(ec_bignum_to_scalar(group(), &one, BN_value_one()));
  ASSERT_TRUE(
      ec_point_mul_scalar_public(group(), &p->raw, &one, &g->raw, &one));
  EXPECT_EQ(0, EC_POINT_cmp(group(), p.get(), two_g.get(), nullptr));
}

// This a regression test for a P-224 bug, but we may as well run it for all
// curves.
TEST_P(ECCurveTest, P224Bug) {
  // P = -G
  const EC_POINT *g = EC_GROUP_get0_generator(group());
  bssl::UniquePtr<EC_POINT> p(EC_POINT_dup(g, group()));
  ASSERT_TRUE(p);
  ASSERT_TRUE(EC_POINT_invert(group(), p.get(), nullptr));

  // Compute 31 * P + 32 * G = G
  bssl::UniquePtr<EC_POINT> ret(EC_POINT_new(group()));
  ASSERT_TRUE(ret);
  bssl::UniquePtr<BIGNUM> bn31(BN_new()), bn32(BN_new());
  ASSERT_TRUE(bn31);
  ASSERT_TRUE(bn32);
  ASSERT_TRUE(BN_set_word(bn31.get(), 31));
  ASSERT_TRUE(BN_set_word(bn32.get(), 32));
  ASSERT_TRUE(EC_POINT_mul(group(), ret.get(), bn32.get(), p.get(), bn31.get(),
                           nullptr));
  EXPECT_EQ(0, EC_POINT_cmp(group(), ret.get(), g, nullptr));

  // Repeat the computation with |ec_point_mul_scalar_public|, which ties the
  // additions together.
  EC_SCALAR sc31, sc32;
  ASSERT_TRUE(ec_bignum_to_scalar(group(), &sc31, bn31.get()));
  ASSERT_TRUE(ec_bignum_to_scalar(group(), &sc32, bn32.get()));
  ASSERT_TRUE(
      ec_point_mul_scalar_public(group(), &ret->raw, &sc32, &p->raw, &sc31));
  EXPECT_EQ(0, EC_POINT_cmp(group(), ret.get(), g, nullptr));
}

TEST_P(ECCurveTest, GPlusMinusG) {
  const EC_POINT *g = EC_GROUP_get0_generator(group());
  bssl::UniquePtr<EC_POINT> p(EC_POINT_dup(g, group()));
  ASSERT_TRUE(p);
  ASSERT_TRUE(EC_POINT_invert(group(), p.get(), nullptr));
  bssl::UniquePtr<EC_POINT> sum(EC_POINT_new(group()));

  ASSERT_TRUE(EC_POINT_add(group(), sum.get(), g, p.get(), nullptr));
  EXPECT_TRUE(EC_POINT_is_at_infinity(group(), sum.get()));
}

static std::vector<EC_builtin_curve> AllCurves() {
  const size_t num_curves = EC_get_builtin_curves(nullptr, 0);
  std::vector<EC_builtin_curve> curves(num_curves);
  EC_get_builtin_curves(curves.data(), num_curves);
  return curves;
}

static std::string CurveToString(
    const testing::TestParamInfo<EC_builtin_curve> &params) {
  // The comment field contains characters GTest rejects, so use the OBJ name.
  return OBJ_nid2sn(params.param.nid);
}

INSTANTIATE_TEST_SUITE_P(All, ECCurveTest, testing::ValuesIn(AllCurves()),
                         CurveToString);

static bssl::UniquePtr<EC_GROUP> GetCurve(FileTest *t, const char *key) {
  std::string curve_name;
  if (!t->GetAttribute(&curve_name, key)) {
    return nullptr;
  }

  if (curve_name == "P-224") {
    return bssl::UniquePtr<EC_GROUP>(EC_GROUP_new_by_curve_name(NID_secp224r1));
  }
  if (curve_name == "P-256") {
    return bssl::UniquePtr<EC_GROUP>(EC_GROUP_new_by_curve_name(
        NID_X9_62_prime256v1));
  }
  if (curve_name == "P-384") {
    return bssl::UniquePtr<EC_GROUP>(EC_GROUP_new_by_curve_name(NID_secp384r1));
  }
  if (curve_name == "P-521") {
    return bssl::UniquePtr<EC_GROUP>(EC_GROUP_new_by_curve_name(NID_secp521r1));
  }

  t->PrintLine("Unknown curve '%s'", curve_name.c_str());
  return nullptr;
}

static bssl::UniquePtr<BIGNUM> GetBIGNUM(FileTest *t, const char *key) {
  std::vector<uint8_t> bytes;
  if (!t->GetBytes(&bytes, key)) {
    return nullptr;
  }

  return bssl::UniquePtr<BIGNUM>(
      BN_bin2bn(bytes.data(), bytes.size(), nullptr));
}

TEST(ECTest, ScalarBaseMultVectors) {
  bssl::UniquePtr<BN_CTX> ctx(BN_CTX_new());
  ASSERT_TRUE(ctx);

  FileTestGTest("crypto/fipsmodule/ec/ec_scalar_base_mult_tests.txt",
                [&](FileTest *t) {
    bssl::UniquePtr<EC_GROUP> group = GetCurve(t, "Curve");
    ASSERT_TRUE(group);
    bssl::UniquePtr<BIGNUM> n = GetBIGNUM(t, "N");
    ASSERT_TRUE(n);
    bssl::UniquePtr<BIGNUM> x = GetBIGNUM(t, "X");
    ASSERT_TRUE(x);
    bssl::UniquePtr<BIGNUM> y = GetBIGNUM(t, "Y");
    ASSERT_TRUE(y);
    bool is_infinity = BN_is_zero(x.get()) && BN_is_zero(y.get());

    bssl::UniquePtr<BIGNUM> px(BN_new());
    ASSERT_TRUE(px);
    bssl::UniquePtr<BIGNUM> py(BN_new());
    ASSERT_TRUE(py);
    auto check_point = [&](const EC_POINT *p) {
      if (is_infinity) {
        EXPECT_TRUE(EC_POINT_is_at_infinity(group.get(), p));
      } else {
        ASSERT_TRUE(EC_POINT_get_affine_coordinates_GFp(
            group.get(), p, px.get(), py.get(), ctx.get()));
        EXPECT_EQ(0, BN_cmp(x.get(), px.get()));
        EXPECT_EQ(0, BN_cmp(y.get(), py.get()));
      }
    };

    const EC_POINT *g = EC_GROUP_get0_generator(group.get());
    bssl::UniquePtr<EC_POINT> p(EC_POINT_new(group.get()));
    ASSERT_TRUE(p);
    // Test single-point multiplication.
    ASSERT_TRUE(EC_POINT_mul(group.get(), p.get(), n.get(), nullptr, nullptr,
                             ctx.get()));
    check_point(p.get());

    ASSERT_TRUE(
        EC_POINT_mul(group.get(), p.get(), nullptr, g, n.get(), ctx.get()));
    check_point(p.get());
  });
}

// These tests take a very long time, but are worth running when we make
// non-trivial changes to the EC code.
TEST(ECTest, DISABLED_ScalarBaseMultVectorsTwoPoint) {
  bssl::UniquePtr<BN_CTX> ctx(BN_CTX_new());
  ASSERT_TRUE(ctx);

  FileTestGTest("crypto/fipsmodule/ec/ec_scalar_base_mult_tests.txt",
                [&](FileTest *t) {
    bssl::UniquePtr<EC_GROUP> group = GetCurve(t, "Curve");
    ASSERT_TRUE(group);
    bssl::UniquePtr<BIGNUM> n = GetBIGNUM(t, "N");
    ASSERT_TRUE(n);
    bssl::UniquePtr<BIGNUM> x = GetBIGNUM(t, "X");
    ASSERT_TRUE(x);
    bssl::UniquePtr<BIGNUM> y = GetBIGNUM(t, "Y");
    ASSERT_TRUE(y);
    bool is_infinity = BN_is_zero(x.get()) && BN_is_zero(y.get());

    bssl::UniquePtr<BIGNUM> px(BN_new());
    ASSERT_TRUE(px);
    bssl::UniquePtr<BIGNUM> py(BN_new());
    ASSERT_TRUE(py);
    auto check_point = [&](const EC_POINT *p) {
      if (is_infinity) {
        EXPECT_TRUE(EC_POINT_is_at_infinity(group.get(), p));
      } else {
        ASSERT_TRUE(EC_POINT_get_affine_coordinates_GFp(
            group.get(), p, px.get(), py.get(), ctx.get()));
        EXPECT_EQ(0, BN_cmp(x.get(), px.get()));
        EXPECT_EQ(0, BN_cmp(y.get(), py.get()));
      }
    };

    const EC_POINT *g = EC_GROUP_get0_generator(group.get());
    bssl::UniquePtr<EC_POINT> p(EC_POINT_new(group.get()));
    ASSERT_TRUE(p);
    bssl::UniquePtr<BIGNUM> a(BN_new()), b(BN_new());
    for (int i = -64; i < 64; i++) {
      SCOPED_TRACE(i);
      ASSERT_TRUE(BN_set_word(a.get(), abs(i)));
      if (i < 0) {
        ASSERT_TRUE(BN_sub(a.get(), EC_GROUP_get0_order(group.get()), a.get()));
      }

      ASSERT_TRUE(BN_copy(b.get(), n.get()));
      ASSERT_TRUE(BN_sub(b.get(), b.get(), a.get()));
      if (BN_is_negative(b.get())) {
        ASSERT_TRUE(BN_add(b.get(), b.get(), EC_GROUP_get0_order(group.get())));
      }

      ASSERT_TRUE(
          EC_POINT_mul(group.get(), p.get(), a.get(), g, b.get(), ctx.get()));
      check_point(p.get());

      EC_SCALAR a_scalar, b_scalar;
      ASSERT_TRUE(ec_bignum_to_scalar(group.get(), &a_scalar, a.get()));
      ASSERT_TRUE(ec_bignum_to_scalar(group.get(), &b_scalar, b.get()));
      ASSERT_TRUE(ec_point_mul_scalar_public(group.get(), &p->raw, &a_scalar,
                                             &g->raw, &b_scalar));
      check_point(p.get());
    }
  });
}

static std::vector<uint8_t> HexToBytes(const char *str) {
  std::vector<uint8_t> ret;
  if (!DecodeHex(&ret, str)) {
    abort();
  }
  return ret;
}

TEST(ECTest, DeriveFromSecret) {
  struct DeriveTest {
    int curve;
    std::vector<uint8_t> secret;
    std::vector<uint8_t> expected_priv;
    std::vector<uint8_t> expected_pub;
  };
  const DeriveTest kDeriveTests[] = {
      {NID_X9_62_prime256v1, HexToBytes(""),
       HexToBytes(
           "b98a86a71efb51ebdac4759937b977e9b0c05224675bb2b6a58ba306e237f4b8"),
       HexToBytes(
           "04fbe6cab439918e00231a2ff073cdc25823998864a9eb36f809095a1a919ece875"
           "a145803fbe89a6cde53936e3c6d9c253ed3d38f5f58cae455c27e95645ceda9")},
      {NID_X9_62_prime256v1, HexToBytes("123456"),
       HexToBytes(
           "44a72bc62087b88e5ab7126766177ed0d8f1ed09ad066cd746527fc201105a7e"),
       HexToBytes(
           "04ec0555cd76e991fef7f5504343937d0f38696db3360a4854052cb0d84a377a5a0"
           "ff64c352755c28692b4ae085c2b817db9a1eddbd22e9cf39c12751e0870791b")},
      {NID_X9_62_prime256v1, HexToBytes("00000000000000000000000000000000"),
       HexToBytes(
           "7ca1e2c83e6a5f2c1b3e7d58180226f269930c4b9fbe2a275096079630b7c57d"),
       HexToBytes(
           "0442ef70c8fc0fbe383ed0a0da36f39f9a590f3feebc07863cc858c9a8ef0465731"
           "0408c249bd4d61929c54b71ffe056e6b4fa1eb537039b43d1c175f0ceab0f89")},
      {NID_X9_62_prime256v1,
       HexToBytes(
           "de9c9b35543aaa0fba039e34e8ca9695da3225c7161c9e3a8c70356cac28c780"),
       HexToBytes(
           "659f5abf3b62b9931c29d6ed0722efd2349fa56f54e708cf3272f620f1bc44d0"),
       HexToBytes(
           "046741f806b593bf3a3d4a9d76bdcb9b0d7874633cbea8f42c05e78561f7e8ec362"
           "b9b6f1913ded796fbdafe7f210cea897ac22a4e580c06a60f2659fd09f1830f")},
      {NID_secp384r1, HexToBytes("123456"),
       HexToBytes("95cd90d548997de090c7622708eccb7edc1b1bd78d2422235ad97406dada"
                  "076555309da200096f6e4b36c46002beee89"),
       HexToBytes(
           "04007b2d026aa7636fa912c3f970d62bb6c10fa81c8f3290ed90b2d701696d1c6b9"
           "5af88ce13e962996a7ac37e16527cb5d69bd081b8641d07634cf84b438600ec9434"
           "15ac6bd7a0236f7ab0ea31ece67df03fa11646ea2b75e73d1b5e45b75c18")},
  };

  for (const auto &test : kDeriveTests) {
    SCOPED_TRACE(Bytes(test.secret));
    bssl::UniquePtr<EC_GROUP> group(EC_GROUP_new_by_curve_name(test.curve));
    ASSERT_TRUE(group);
    bssl::UniquePtr<EC_KEY> key(EC_KEY_derive_from_secret(
        group.get(), test.secret.data(), test.secret.size()));
    ASSERT_TRUE(key);

    std::vector<uint8_t> priv(BN_num_bytes(EC_GROUP_get0_order(group.get())));
    ASSERT_TRUE(BN_bn2bin_padded(priv.data(), priv.size(),
                                 EC_KEY_get0_private_key(key.get())));
    EXPECT_EQ(Bytes(priv), Bytes(test.expected_priv));

    uint8_t *pub = nullptr;
    size_t pub_len =
        EC_KEY_key2buf(key.get(), POINT_CONVERSION_UNCOMPRESSED, &pub, nullptr);
    bssl::UniquePtr<uint8_t> free_pub(pub);
    EXPECT_NE(pub_len, 0u);
    EXPECT_EQ(Bytes(pub, pub_len), Bytes(test.expected_pub));
  }
}

TEST(ECTest, HashToCurve) {
  struct HashToCurveTest {
    int (*hash_to_curve)(const EC_GROUP *group, EC_RAW_POINT *out,
                         const uint8_t *dst, size_t dst_len, const uint8_t *msg,
                         size_t msg_len);
    int curve_nid;
    const char *dst;
    const char *msg;
    const char *x_hex;
    const char *y_hex;
  };
  static const HashToCurveTest kTests[] = {
      // See draft-irtf-cfrg-hash-to-curve-06, appendix G.3.1. Note these test
      // |ec_hash_to_curve_p521_xmd_sha512_sswu_ref_for_testing| due to a spec
      // issue. See
      // https://github.com/cfrg/draft-irtf-cfrg-hash-to-curve/issues/237. We
      // expose and test this function to check our consistency with the rest of
      // the reference implementation.
      {&ec_hash_to_curve_p521_xmd_sha512_sswu_ref_for_testing, NID_secp521r1,
       "P521_XMD:SHA-512_SSWU_RO_TESTGEN", "",
       "00ad6cb736cb0565a2b6c52dd9e53f76a9a40a44c73bfaacef03c3"
       "ef62a9a23920b7df4de1b92754de7bb3013d9d36049da001136e7f"
       "4b1b0ba10beac862a2b3d3c5",
       "01c2ecab1b6f7bb6797a4b5bd416b385e891926fc17f230f2406f3"
       "d47076526c5d90bfb4d0170fd8a339de1a66e6304d280d0404fb68"
       "5b2ca07e2742a770b681bf56"},
      {&ec_hash_to_curve_p521_xmd_sha512_sswu_ref_for_testing, NID_secp521r1,
       "P521_XMD:SHA-512_SSWU_RO_TESTGEN", "abcdef0123456789",
       "019f0195e514da4243a4d2de4b7ed2415d5205c6da11eb7deae70b"
       "e78a61bb89ebf17f7c9970ee20b4152ae50c95e55f626bc7350d5a"
       "0f530a91f48047bd90eeeaa7",
       "016eaa02cd5511a96eed4ffc965bdc3f1fdbb7f4c9895eabdf168b"
       "44250278ebca55474bc89a2f246b8fb959010502aab8a9385319bc"
       "f69f74dd8f518bea1c7fafde"},
      {&ec_hash_to_curve_p521_xmd_sha512_sswu_ref_for_testing, NID_secp521r1,
       "P521_XMD:SHA-512_SSWU_RO_TESTGEN",
       "a512_aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
       "00de3dd7780cfcd538f7b3067d8da52c522a031244dc0d327e6e99"
       "ef331be475354a0b481a22e0d4d35b232da260baac5b693a827a20"
       "b1f328a416ffc47ad945a4dc",
       "016bb6c5c965c6a80a4a5e0c2c7bbd841766eac695f88a730076b3"
       "2d4399da01609a4a17b59a21f4f58a174d6110081b96e5aaedead3"
       "cfd4252e74de969680ba74ab"},

      // The above test vectors with the expectations updated to compute
      // hash_to_field correctly.
      {&ec_hash_to_curve_p521_xmd_sha512_sswu, NID_secp521r1,
       "P521_XMD:SHA-512_SSWU_RO_TESTGEN", "",
       "00758617b5e40aa8b30fcfd3c7453ad1abeff158de5697d6f1ccb8"
       "4690aaa8bb6692986200d16206e85e4f39f1d2829fee1a5904a089"
       "b4fab3b76873429877c58f99",
       "016edf324d95fcbe4a30f06751f16cdd5d0b49921dd653cefb3ea2"
       "dc2b5b903e36d9924a65407283588cc6c224ab6d6324c73cdc166c"
       "e1530b46984b459e966349b3"},
      {&ec_hash_to_curve_p521_xmd_sha512_sswu, NID_secp521r1,
       "P521_XMD:SHA-512_SSWU_RO_TESTGEN", "abcdef0123456789",
       "01f58bfb34825d028c392976a09cebee829734f7714c84b8a13580"
       "afcc2eb4726e18e307476c1fccdc857a3d6767fd2882875ab132b7"
       "fa7f3f6bae8954384001b1a1",
       "00ee0d2d0bfb0bdc6215814fe7096a3dfbf020dce4f0645e8e21a9"
       "0d6a6113a5ca61ae7d8f3b485b04f2eb2b85e34fc7f9f1bf367386"
       "2e03932b0acc3655e84d480f"},
      {&ec_hash_to_curve_p521_xmd_sha512_sswu, NID_secp521r1,
       "P521_XMD:SHA-512_SSWU_RO_TESTGEN",
       "a512_aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
       "016d9a90619bb20c49a2a73cc8c6218cd9b3fb13c720fff2e1f8db"
       "ac92862c7da4faf404faeff6b64f0d9b1c5824cec99b0d0ed02b3f"
       "acb6275ce553404ea361503e",
       "007e301e3357fb1d53961c56e53ce2763e44b297062a3eb14b9f8d"
       "6aadc92162a74f7e254a606275e76ea0ac343b3bc746f99804bacd"
       "7351a76fce44347c72a6fe9a"},

      // Custom test vector which triggers long DST path.
      {&ec_hash_to_curve_p521_xmd_sha512_sswu, NID_secp521r1,
       "P521_XMD:SHA-512_SSWU_RO_TESTGEN_aaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
       "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
       "abcdef0123456789",
       "0036b0c8bbec60335ff8b0397c2cb80283b97051cc949c5c190c28"
       "92b279fafd6c372dcec3e71eab85c48ed440c14498332548ee46d0"
       "c85442cbdc5b4032e86c3884",
       "0081e32ca4378ae89b03142361d9c7fbe66acf0351aca3a71eca50"
       "7a37fb8673b69cb108d079a248aedd74f06949d6623e7f7605ea10"
       "f6f751ab574c005db7377d7f"},
  };

  for (const auto &test : kTests) {
    SCOPED_TRACE(test.dst);
    SCOPED_TRACE(test.msg);

    bssl::UniquePtr<EC_GROUP> group(EC_GROUP_new_by_curve_name(test.curve_nid));
    ASSERT_TRUE(group);
    bssl::UniquePtr<EC_POINT> p(EC_POINT_new(group.get()));
    ASSERT_TRUE(p);
    ASSERT_TRUE(test.hash_to_curve(
        group.get(), &p->raw, reinterpret_cast<const uint8_t *>(test.dst),
        strlen(test.dst), reinterpret_cast<const uint8_t *>(test.msg),
        strlen(test.msg)));

    std::vector<uint8_t> buf;
    ASSERT_TRUE(EncodeECPoint(&buf, group.get(), p.get(),
                              POINT_CONVERSION_UNCOMPRESSED));
    size_t field_len = (buf.size() - 1) / 2;
    EXPECT_EQ(test.x_hex,
              EncodeHex(bssl::MakeConstSpan(buf).subspan(1, field_len)));
    EXPECT_EQ(test.y_hex, EncodeHex(bssl::MakeConstSpan(buf).subspan(
                              1 + field_len, field_len)));
  }
}
