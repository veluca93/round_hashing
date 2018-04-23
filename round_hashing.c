#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CLK CLOCK_PROCESS_CPUTIME_ID

uint64_t hash_param;

uint64_t rotl(uint64_t x, int k) { return (x << k) | (x >> (64 - k)); }

size_t HashValue(uint64_t val, uint64_t mod_pow) {
  uint64_t s0 = val;
  uint64_t s1 = hash_param;

  s1 ^= s0;
  s0 = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
  s1 = rotl(s1, 36);                   // c
  uint64_t hash1 = s0 + s1;
  hash1 = hash1 & ((1ULL << mod_pow) - 1);
  return hash1;
}

uint64_t *data;
long long N;
uint64_t s[2] = {0, 1};

uint64_t rng() {
  const uint64_t s0 = s[0];
  uint64_t s1 = s[1];
  const uint64_t result = s0 + s1;

  s1 ^= s0;
  s[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
  s[1] = rotl(s1, 36);                   // c
  return result;
}

uint64_t num_long_arcs_;
uint64_t num_short_arc_groups_;
uint64_t num_short_arcs_;
uint64_t current_s_;
uint64_t S_;
uint64_t S_minus_one_;
uint64_t S_log_;
uint64_t arc_groups_;
uint64_t num_buckets_;
uint64_t a_, b_;

uint64_t lh_n, lh_n0, lh_l, lh_p, lh_x;

uint64_t NumBuckets() { return num_long_arcs_ + num_short_arcs_; }

void NewBucket() {
  assert(num_short_arcs_ == num_short_arc_groups_ * (current_s_ + 1));
  // Simple case: we can change all the hashes
  if (NumBuckets() < S_) {
    num_long_arcs_++;
    return;
  }
  num_long_arcs_ -= current_s_;
  num_short_arc_groups_++;
  num_short_arcs_ += current_s_ + 1;
  // If we are done going around the circle ...
  if (num_long_arcs_ == 0) {
    num_long_arcs_ = num_short_arcs_;
    num_short_arc_groups_ = 0;
    num_short_arcs_ = 0;
    current_s_++;
  }
  // If we completed a doubling...
  if (current_s_ == 2 * S_) {
    current_s_ = S_;
    arc_groups_ *= 2;
  }
}

#define DIVF(i)                                                                \
  uint64_t div##i(uint64_t a) { return a / i; }
DIVF(1);
DIVF(2);
DIVF(3);
DIVF(4);
DIVF(5);
DIVF(6);
DIVF(7);
DIVF(8);
DIVF(9);
DIVF(10);
DIVF(11);
DIVF(12);
DIVF(13);
DIVF(14);
DIVF(15);
DIVF(16);
DIVF(17);
DIVF(18);
DIVF(19);
DIVF(20);
DIVF(21);
DIVF(22);
DIVF(23);
DIVF(24);
DIVF(25);
DIVF(26);
DIVF(27);
DIVF(28);
DIVF(29);
DIVF(30);
DIVF(31);
DIVF(32);
DIVF(33);
DIVF(34);
DIVF(35);
DIVF(36);
DIVF(37);
DIVF(38);
DIVF(39);
DIVF(40);
DIVF(41);
DIVF(42);
DIVF(43);
DIVF(44);
DIVF(45);
DIVF(46);
DIVF(47);
DIVF(48);
DIVF(49);
DIVF(50);
DIVF(51);
DIVF(52);
DIVF(53);
DIVF(54);
DIVF(55);
DIVF(56);
DIVF(57);
DIVF(58);
DIVF(59);
DIVF(60);
DIVF(61);
DIVF(62);
DIVF(63);
DIVF(64);
DIVF(65);
DIVF(66);
DIVF(67);
DIVF(68);
DIVF(69);
DIVF(70);
DIVF(71);
DIVF(72);
DIVF(73);
DIVF(74);
DIVF(75);
DIVF(76);
DIVF(77);
DIVF(78);
DIVF(79);
DIVF(80);
DIVF(81);
DIVF(82);
DIVF(83);
DIVF(84);
DIVF(85);
DIVF(86);
DIVF(87);
DIVF(88);
DIVF(89);
DIVF(90);
DIVF(91);
DIVF(92);
DIVF(93);
DIVF(94);
DIVF(95);
DIVF(96);
DIVF(97);
DIVF(98);
DIVF(99);
DIVF(100);
DIVF(101);
DIVF(102);
DIVF(103);
DIVF(104);
DIVF(105);
DIVF(106);
DIVF(107);
DIVF(108);
DIVF(109);
DIVF(110);
DIVF(111);
DIVF(112);
DIVF(113);
DIVF(114);
DIVF(115);
DIVF(116);
DIVF(117);
DIVF(118);
DIVF(119);
DIVF(120);
DIVF(121);
DIVF(122);
DIVF(123);
DIVF(124);
DIVF(125);
DIVF(126);
DIVF(127);
DIVF(128);
DIVF(129);
DIVF(130);
DIVF(131);
DIVF(132);
DIVF(133);
DIVF(134);
DIVF(135);
DIVF(136);
DIVF(137);
DIVF(138);
DIVF(139);
DIVF(140);
DIVF(141);
DIVF(142);
DIVF(143);
DIVF(144);
DIVF(145);
DIVF(146);
DIVF(147);
DIVF(148);
DIVF(149);
DIVF(150);
DIVF(151);
DIVF(152);
DIVF(153);
DIVF(154);
DIVF(155);
DIVF(156);
DIVF(157);
DIVF(158);
DIVF(159);
DIVF(160);
DIVF(161);
DIVF(162);
DIVF(163);
DIVF(164);
DIVF(165);
DIVF(166);
DIVF(167);
DIVF(168);
DIVF(169);
DIVF(170);
DIVF(171);
DIVF(172);
DIVF(173);
DIVF(174);
DIVF(175);
DIVF(176);
DIVF(177);
DIVF(178);
DIVF(179);
DIVF(180);
DIVF(181);
DIVF(182);
DIVF(183);
DIVF(184);
DIVF(185);
DIVF(186);
DIVF(187);
DIVF(188);
DIVF(189);
DIVF(190);
DIVF(191);
DIVF(192);
DIVF(193);
DIVF(194);
DIVF(195);
DIVF(196);
DIVF(197);
DIVF(198);
DIVF(199);
DIVF(200);
DIVF(201);
DIVF(202);
DIVF(203);
DIVF(204);
DIVF(205);
DIVF(206);
DIVF(207);
DIVF(208);
DIVF(209);
DIVF(210);
DIVF(211);
DIVF(212);
DIVF(213);
DIVF(214);
DIVF(215);
DIVF(216);
DIVF(217);
DIVF(218);
DIVF(219);
DIVF(220);
DIVF(221);
DIVF(222);
DIVF(223);
DIVF(224);
DIVF(225);
DIVF(226);
DIVF(227);
DIVF(228);
DIVF(229);
DIVF(230);
DIVF(231);
DIVF(232);
DIVF(233);
DIVF(234);
DIVF(235);
DIVF(236);
DIVF(237);
DIVF(238);
DIVF(239);
DIVF(240);
DIVF(241);
DIVF(242);
DIVF(243);
DIVF(244);
DIVF(245);
DIVF(246);
DIVF(247);
DIVF(248);
DIVF(249);
DIVF(250);
DIVF(251);
DIVF(252);
DIVF(253);
DIVF(254);
DIVF(255);
DIVF(256);
DIVF(257);
DIVF(258);
DIVF(259);

uint64_t (*divf[])(uint64_t) = {
    NULL,   div1,   div2,   div3,   div4,   div5,   div6,   div7,   div8,
    div9,   div10,  div11,  div12,  div13,  div14,  div15,  div16,  div17,
    div18,  div19,  div20,  div21,  div22,  div23,  div24,  div25,  div26,
    div27,  div28,  div29,  div30,  div31,  div32,  div33,  div34,  div35,
    div36,  div37,  div38,  div39,  div40,  div41,  div42,  div43,  div44,
    div45,  div46,  div47,  div48,  div49,  div50,  div51,  div52,  div53,
    div54,  div55,  div56,  div57,  div58,  div59,  div60,  div61,  div62,
    div63,  div64,  div65,  div66,  div67,  div68,  div69,  div70,  div71,
    div72,  div73,  div74,  div75,  div76,  div77,  div78,  div79,  div80,
    div81,  div82,  div83,  div84,  div85,  div86,  div87,  div88,  div89,
    div90,  div91,  div92,  div93,  div94,  div95,  div96,  div97,  div98,
    div99,  div100, div101, div102, div103, div104, div105, div106, div107,
    div108, div109, div110, div111, div112, div113, div114, div115, div116,
    div117, div118, div119, div120, div121, div122, div123, div124, div125,
    div126, div127, div128, div129, div130, div131, div132, div133, div134,
    div135, div136, div137, div138, div139, div140, div141, div142, div143,
    div144, div145, div146, div147, div148, div149, div150, div151, div152,
    div153, div154, div155, div156, div157, div158, div159, div160, div161,
    div162, div163, div164, div165, div166, div167, div168, div169, div170,
    div171, div172, div173, div174, div175, div176, div177, div178, div179,
    div180, div181, div182, div183, div184, div185, div186, div187, div188,
    div189, div190, div191, div192, div193, div194, div195, div196, div197,
    div198, div199, div200, div201, div202, div203, div204, div205, div206,
    div207, div208, div209, div210, div211, div212, div213, div214, div215,
    div216, div217, div218, div219, div220, div221, div222, div223, div224,
    div225, div226, div227, div228, div229, div230, div231, div232, div233,
    div234, div235, div236, div237, div238, div239, div240, div241, div242,
    div243, div244, div245, div246, div247, div248, div249, div250, div251,
    div252, div253, div254, div255, div256, div257, div258, div259};

void InitHash(uint64_t S, uint64_t num_buckets) {
  S_ = S;
  num_long_arcs_ = 1;
  num_short_arc_groups_ = 0;
  num_short_arcs_ = 0;
  current_s_ = S_;
  arc_groups_ = 1;
  num_buckets_ = num_buckets;
  S_minus_one_ = S_ - 1;
  S_log_ = 0;
  while ((1 << S_log_) < S_) {
    S_log_++;
  }
  assert((1 << S_log_) == S_);
  for (size_t i = 1; i < num_buckets; i++) {
    NewBucket();
  }
  lh_n0 = S;
  uint64_t lh_2n0m1 = 2 * S - 1;
  lh_l = 0;
  lh_x = S_log_;
  while ((num_buckets >> lh_l) > lh_2n0m1) {
    lh_l++;
  }
  lh_n = num_buckets >> lh_l;
  lh_p = num_buckets - (lh_n << lh_l);
}

size_t ArcNum(uint64_t divs, uint64_t hash) {
  uint64_t divs1 = divs >> 32;
  uint64_t divs0 = divs & 0xffffffff;
  uint64_t hash1 = hash >> 32;
  uint64_t hash0 = hash & 0xffffffff;
  uint64_t low = (hash0 * divs0) >> 32;
  size_t new_num =
      (hash1 * divs1 << 2) + ((hash1 * divs0 + hash0 * divs1 + low) >> 28);
  return new_num;
}

size_t HashToArc(uint64_t hash) {
  if (NumBuckets() < S_) {
    return ArcNum(NumBuckets(), hash);
  }
  size_t arc_candidate = ArcNum((current_s_ + 1) * arc_groups_, hash);
  if (arc_candidate < num_short_arcs_) {
    return arc_candidate;
  }
  arc_candidate =
      ArcNum(current_s_ * arc_groups_, hash) + num_short_arc_groups_;
  return arc_candidate;
}

size_t ArcToBucket(size_t arc_num) {
  // The first S_ arcs are mapped onto themselves.
  if (arc_num < S_) {
    return arc_num;
  }
  uint64_t s_to_use = current_s_ + (num_short_arcs_ > arc_num);
  arc_num -= num_short_arc_groups_ & -(num_short_arcs_ <= arc_num);
#ifdef HARDCODE_DIVISION
  size_t arc_group = divf[s_to_use](arc_num);
#else
  size_t arc_group = arc_num / s_to_use;
#endif
  size_t position_in_group = arc_num - arc_group * s_to_use;
  size_t initial_groups_ = arc_groups_;
  if (s_to_use > S_) {
    initial_groups_ <<= 1;
    arc_group <<= 1;
    arc_group += (position_in_group >> S_log_);
    position_in_group &= S_minus_one_;
  }
  size_t dist = __builtin_ctzll(arc_group);
  size_t new_ret =
      ((S_ + position_in_group) * initial_groups_ + arc_group) >> (dist + 1);
  return new_ret;
}

size_t RoundHash(uint64_t value) {
#ifndef ASSUME_HASHED
  value = HashValue(value, 60);
#endif
  const size_t arc = HashToArc(value);
  const size_t bucket = ArcToBucket(arc);
  return bucket;
}

size_t JumpConsistentHash(uint64_t key) {
  int64_t b = 1, j = 0;
  while (j < num_buckets_) {
    b = j;
    key = key * 2862933555777941757ULL + 1;
    j = (b + 1) * (((double)(1LL << 31)) / ((double)((key >> 33) + 1)));
  }
  return b;
}

uint64_t LinearHash(uint64_t K) {
  uint64_t h = HashValue(K, lh_x);
  uint64_t s = 1;
  uint64_t sm1 = 0;
  K = HashValue(K, 63);
  for (uint64_t j = 0; j < lh_l; j++) {
    if (HashValue(K, lh_x + 1) >= lh_n0) {
      h = (h & sm1) + s * HashValue(K, lh_x + 1);
    }
    K = HashValue(K, 63);
    s = 2 * s;
    sm1 = s - 1;
  }
  uint64_t q = lh_n + ((h & sm1) < lh_p);
  uint64_t u = HashValue(K, lh_x + 1);
  K = HashValue(K, 63);
  while (u >= q) {
    u = HashValue(K, lh_x + 1);
    K = HashValue(K, 63);
  }
  if (u >= lh_n0) {
    h = (h & sm1) + s * u;
  }
  return h;
}

int cmp(const void *a, const void *b) {
  int64_t x = *(const int64_t *)a;
  int64_t y = *(const int64_t *)b;
  return x - y;
}

void RunSingleTest(const char *testname, size_t (*testfun)(uint64_t)) {
  printf("\033[;31mTesting %s\033[;m\n", testname);
  uint64_t *bucket_counts = malloc(sizeof(int64_t) * num_buckets_);
  for (long long i = 0; i < num_buckets_; i++) {
    bucket_counts[i] = 0;
  }
  for (long long i = 0; i < N; i++) {
    uint64_t x = testfun(data[i]);
    bucket_counts[x]++;
  }
  size_t tmp = 0;
  struct timespec start;
  struct timespec end;
  clock_gettime(CLK, &start);
  for (long long i = 0; i < N; i++) {
    tmp += testfun(data[i]);
  }
  clock_gettime(CLK, &end);
  long long elapsed_ns = (long long)(end.tv_sec - start.tv_sec) * 1000000000 +
                         (long long)(end.tv_nsec - start.tv_nsec);
  printf("% 12lldns elapsed (% 12.2lFns per item)\n", elapsed_ns,
         (double)elapsed_ns / N);
  double stddev = 0;
  int64_t min = bucket_counts[0];
  int64_t max = bucket_counts[0];
  for (long long i = 0; i < num_buckets_; i++) {
    double off = (bucket_counts[i] - (double)N / num_buckets_);
    stddev += off * off;
    if (bucket_counts[i] < min)
      min = bucket_counts[i];
    if (bucket_counts[i] > max)
      max = bucket_counts[i];
  }
  stddev = sqrt(stddev);
  qsort(bucket_counts, num_buckets_, sizeof(int64_t), cmp);
  int64_t low99 = bucket_counts[(int)(0.01 * num_buckets_)];
  int64_t high99 = bucket_counts[(int)(0.99 * num_buckets_)];
  printf("    From % 12ld to % 12ld elements in buckets (% 12lF to % 12lF)\n",
         min, max, (double)min * num_buckets_ / N,
         (double)max * num_buckets_ / N);
  printf("99p from % 12ld to % 12ld elements in buckets (% 12lF "
         "to % 12lF)\n",
         low99, high99, (double)low99 * num_buckets_ / N,
         (double)high99 * num_buckets_ / N);
  printf("stddev: % 16.4lF  stddev/mean: % 16.4lF\n", stddev,
         stddev * num_buckets_ / N);
  free(bucket_counts);
}

void RunBaseline() {
  uint64_t tmp = 0;
  struct timespec start;
  struct timespec end;
  printf("\033[;31mTime to compute hashes of all the values\033[;m\n");
  clock_gettime(CLK, &start);
  for (long long i = 0; i < N; i++) {
    tmp += HashValue(data[i], 60);
  }
  clock_gettime(CLK, &end);
  printf("Random value: %lu\n", tmp);
  long long elapsed_ns = (long long)(end.tv_sec - start.tv_sec) * 1000000000 +
                         (long long)(end.tv_nsec - start.tv_nsec);
  printf("% 12lldns elapsed (% 12.2lFns per item)\n", elapsed_ns,
         (double)elapsed_ns / N);
  printf("\033[;31mTime to compute the sum of all the values\033[;m\n");
  clock_gettime(CLK, &start);
  for (long long i = 0; i < N; i++) {
    tmp += data[i];
  }
  clock_gettime(CLK, &end);
  elapsed_ns = (long long)(end.tv_sec - start.tv_sec) * 1000000000 +
               (long long)(end.tv_nsec - start.tv_nsec);
  printf("% 12lldns elapsed (% 12.2lFns per item)\n", elapsed_ns,
         (double)elapsed_ns / N);
  printf("Random value: %lu\n", tmp);
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s N num_server\n", argv[0]);
    return 1;
  }
  N = atoll(argv[1]);
  long long range = atoll(argv[2]);
  data = malloc(sizeof(uint64_t) * N);
#ifndef UNIFORM_DATA
  const char *cache_file = ".data";
  FILE *f = fopen(cache_file, "r");
  size_t cached_values = 0;
  if (f) {
    fseek(f, 0L, SEEK_END);
    cached_values = ftell(f) / sizeof(uint64_t);
    fseek(f, 0L, SEEK_SET);
  }
  rng();
  hash_param = rng();
  if (f && N <= cached_values) {
    fread(data, sizeof(uint64_t), N, f);
  } else {
    if (f)
      fclose(f);
    for (size_t i = 0; i < N; i++) {
      data[i] = rng() % (1ULL << 60);
    }
    f = fopen(cache_file, "w");
    if (!f) {
      fprintf(stderr, "Could not open cache file\n");
    } else {
      fwrite(data, sizeof(uint64_t), N, f);
    }
  }
#else
  for (uint64_t i = 0; i < N; i++) {
    __int128_t val = 1ULL << 60;
    data[i] = val * i / (N + 1);
  }
#endif

  printf("Testing hash functions with %lld servers\n", range);
  InitHash(1, range);
  RunSingleTest("JumpHash", JumpConsistentHash);
  RunSingleTest("RoundHash1", RoundHash);
  RunSingleTest("LinearHash1", LinearHash);
  InitHash(2, range);
  RunSingleTest("RoundHash2", RoundHash);
  RunSingleTest("LinearHash2", LinearHash);
  InitHash(4, range);
  RunSingleTest("RoundHash4", RoundHash);
  RunSingleTest("LinearHash4", LinearHash);
  InitHash(8, range);
  RunSingleTest("RoundHash8", RoundHash);
  RunSingleTest("LinearHash8", LinearHash);
  InitHash(16, range);
  RunSingleTest("RoundHash16", RoundHash);
  RunSingleTest("LinearHash16", LinearHash);
  InitHash(32, range);
  RunSingleTest("RoundHash32", RoundHash);
  RunSingleTest("LinearHash32", LinearHash);
  InitHash(64, range);
  RunSingleTest("RoundHash64", RoundHash);
  RunSingleTest("LinearHash64", LinearHash);
  InitHash(128, range);
  RunSingleTest("RoundHash128", RoundHash);
  RunSingleTest("LinearHash128", LinearHash);
  RunBaseline();
}
