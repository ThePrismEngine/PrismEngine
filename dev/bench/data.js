window.BENCHMARK_DATA = {
  "lastUpdate": 1771075423980,
  "repoUrl": "https://github.com/ThePrismEngine/PrismEngine",
  "entries": {
    "ECS Benchmarks": [
      {
        "commit": {
          "author": {
            "email": "140196384+Aleksei-Kutuzov@users.noreply.github.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "noreply@github.com",
            "name": "GitHub",
            "username": "web-flow"
          },
          "distinct": true,
          "id": "5c185208bc998a5abd885b9071a015a3c6daba1f",
          "message": "Change branch reference from 'main' to 'master'",
          "timestamp": "2026-02-13T21:48:02+03:00",
          "tree_id": "38fa00d6671c657343880fe0e1f520ef2a92b5a4",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/5c185208bc998a5abd885b9071a015a3c6daba1f"
        },
        "date": 1771008564821,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.4541507758527548,
            "unit": "ns/iter",
            "extra": "iterations: 194782609\ncpu: 3.3691406197357177 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 294.2789550894636,
            "unit": "ns/iter",
            "extra": "iterations: 1947826\ncpu: 304.82702253692065 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 412.83740603470534,
            "unit": "ns/iter",
            "extra": "iterations: 1824582\ncpu: 411.0530521511228 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 390.90485492253106,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 401.08816964285717 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 29.705062740926856,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 28.49469910594396 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 30.786486607143257,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 29.994419642857142 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 30.566302095684385,
            "unit": "ns/iter",
            "extra": "iterations: 24888889\ncpu: 30.7617186126709 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 31.28807392637844,
            "unit": "ns/iter",
            "extra": "iterations: 21333333\ncpu: 31.494141117095953 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 30.55351878097024,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 30.482701369149353 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 30.43327592194649,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 30.482701369149353 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 30.47686141369931,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 30.482701369149353 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 30.45118596687026,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 29.820033948080887 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 30.4531580651152,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 30.482701369149353 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 8384.600961603026,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 8370.498345989527 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 16217.238839286401,
            "unit": "ns/iter",
            "extra": "iterations: 44800\ncpu: 15694.754464285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 32513.883928572286,
            "unit": "ns/iter",
            "extra": "iterations: 22400\ncpu: 32784.59821428572 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 66772.08705356818,
            "unit": "ns/iter",
            "extra": "iterations: 8960\ncpu: 64522.87946428572 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 137992.9891522672,
            "unit": "ns/iter",
            "extra": "iterations: 4978\ncpu: 138107.67376456407 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 305235.4537743754,
            "unit": "ns/iter",
            "extra": "iterations: 2358\ncpu: 298187.0229007634 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 632672.5892857306,
            "unit": "ns/iter",
            "extra": "iterations: 1120\ncpu: 627790.1785714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 1298738.616071406,
            "unit": "ns/iter",
            "extra": "iterations: 448\ncpu: 1290457.5892857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 53.43994999999495,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 54.6875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.784457136098915,
            "unit": "ns/iter",
            "extra": "iterations: 186666667\ncpu: 3.766741064702248 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.992232142857189,
            "unit": "ns/iter",
            "extra": "iterations: 112000000\ncpu: 5.859375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 11.070748437500555,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 10.986328125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 19.175502265743894,
            "unit": "ns/iter",
            "extra": "iterations: 34461538\ncpu: 19.04296900503976 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 37.703592183863215,
            "unit": "ns/iter",
            "extra": "iterations: 18666667\ncpu: 36.8303564851722 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 75.88628348213737,
            "unit": "ns/iter",
            "extra": "iterations: 8960000\ncpu: 74.98604910714286 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 17.354450892857237,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.741071428571427 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.444481189979763,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 13.497488779029068 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "59bea5b3dab50e51dd9fed0b511451f9dfce51c3",
          "message": "Merge branch 'master' of https://github.com/Aleksei-Kutuzov/PrismEngine",
          "timestamp": "2026-02-13T22:43:22+03:00",
          "tree_id": "eb428fc94936e74af2375317d2f5709cc30bdec7",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/59bea5b3dab50e51dd9fed0b511451f9dfce51c3"
        },
        "date": 1771011887285,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.5015337437472707,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.529575886554329 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 291.60234243123335,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 285.64457588196495 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 414.6250573829893,
            "unit": "ns/iter",
            "extra": "iterations: 1723077\ncpu: 371.79127804503224 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 393.8786607201499,
            "unit": "ns/iter",
            "extra": "iterations: 1120000\ncpu: 446.42857142857144 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 30.19911607142894,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 29.994419642857142 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 30.84732749091839,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 31.145368790217816 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 30.769379464285407,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 30.691964285714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 30.927290178571603,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 29.296875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 30.85651365177567,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 31.145368790217816 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 30.865022321428118,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 30.691964285714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 30.848776785713994,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 30.691964285714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 31.04690178571496,
            "unit": "ns/iter",
            "extra": "iterations: 22400000\ncpu: 31.389508928571427 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 30.81607503507203,
            "unit": "ns/iter",
            "extra": "iterations: 23578947\ncpu: 30.482701369149353 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 8237.876116071582,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 8196.14955357143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 16284.381696428492,
            "unit": "ns/iter",
            "extra": "iterations: 44800\ncpu: 16043.526785714286 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 32127.478554352045,
            "unit": "ns/iter",
            "extra": "iterations: 21333\ncpu: 32227.066047907 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 66014.6517857133,
            "unit": "ns/iter",
            "extra": "iterations: 11200\ncpu: 64174.107142857145 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 136497.85054238807,
            "unit": "ns/iter",
            "extra": "iterations: 4978\ncpu: 134968.86299718762 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 296423.3828846966,
            "unit": "ns/iter",
            "extra": "iterations: 2489\ncpu: 301325.8336681398 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 632935.3571428545,
            "unit": "ns/iter",
            "extra": "iterations: 1120\ncpu: 627790.1785714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 1285042.8571428626,
            "unit": "ns/iter",
            "extra": "iterations: 448\ncpu: 1290457.5892857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 54.82468749999977,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 55.80357142857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.466222761667462,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.452845975977061 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.419542857142697,
            "unit": "ns/iter",
            "extra": "iterations: 112000000\ncpu: 5.440848214285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 9.77195937499964,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 9.765625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 16.630244308279394,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.49693069310091 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 32.62902238482808,
            "unit": "ns/iter",
            "extra": "iterations: 21333333\ncpu: 32.95898488998414 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 62.7227767857162,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 62.779017857142854 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 17.32609569041159,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.159598367496415 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.569237662637754,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 13.497488779029068 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "0f07dd6e0a4b2ec7d113a723d93d4624b5e6638b",
          "message": "update: optimising ComponentManager class",
          "timestamp": "2026-02-14T00:04:45+03:00",
          "tree_id": "a3bdc53258df908479e63519fdf654d19dbd2bd0",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/0f07dd6e0a4b2ec7d113a723d93d4624b5e6638b"
        },
        "date": 1771016771178,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.485445261633203,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.452845975977061 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 270.31082589287377,
            "unit": "ns/iter",
            "extra": "iterations: 1792000\ncpu: 313.8950892857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 306.87150107147545,
            "unit": "ns/iter",
            "extra": "iterations: 2133333\ncpu: 314.9414554596024 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 307.0190300096239,
            "unit": "ns/iter",
            "extra": "iterations: 2036364\ncpu: 337.6115468550809 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 17.06393080357138,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.741071428571427 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 19.68419294854325,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 19.182477550117337 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 16.10488627608347,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.113281142098565 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 16.506694196428537,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 15.694754464285714 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 16.9667460917403,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.49693069310091 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 16.202229838382912,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 16.32254456998864 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 16.220247767856833,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.392299107142858 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 16.091696097600455,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.113281142098565 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 16.175816632751197,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 16.113281142098565 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 7159.675223214558,
            "unit": "ns/iter",
            "extra": "iterations: 89600\ncpu: 7149.832589285715 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 15153.542410713935,
            "unit": "ns/iter",
            "extra": "iterations: 44800\ncpu: 14648.4375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 29962.02553119331,
            "unit": "ns/iter",
            "extra": "iterations: 23579\ncpu: 29819.9669197167 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 61893.52678571427,
            "unit": "ns/iter",
            "extra": "iterations: 11200\ncpu: 61383.92857142857 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 126564.3392857133,
            "unit": "ns/iter",
            "extra": "iterations: 5600\ncpu: 128348.21428571429 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 276108.462998103,
            "unit": "ns/iter",
            "extra": "iterations: 2635\ncpu: 278700.1897533207 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 622840.4017857134,
            "unit": "ns/iter",
            "extra": "iterations: 896\ncpu: 592912.9464285715 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 1377577.5100401642,
            "unit": "ns/iter",
            "extra": "iterations: 498\ncpu: 1380522.0883534136 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 53.788071428572586,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 54.408482142857146 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.453682761689861,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.452845975977061 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.335022999999808,
            "unit": "ns/iter",
            "extra": "iterations: 100000000\ncpu: 5.3125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 9.758880760005074,
            "unit": "ns/iter",
            "extra": "iterations: 74666667\ncpu: 9.83537942037777 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 16.66008482142838,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.741071428571427 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 32.699555198431405,
            "unit": "ns/iter",
            "extra": "iterations: 21333333\ncpu: 32.95898488998414 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 62.766249999999246,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 62.779017857142854 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 19.565029556484436,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 19.566127101119683 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.970219803704177,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 13.811383866913465 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "0201e8a219447f34556c86394d0031225482a842",
          "message": "optimization: ComponentManager",
          "timestamp": "2026-02-14T13:35:11+03:00",
          "tree_id": "8a0a92253f28872d575866678e83bbcac87a51f2",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/0201e8a219447f34556c86394d0031225482a842"
        },
        "date": 1771065398532,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.513726065154049,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.529575886554329 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 275.51333146690996,
            "unit": "ns/iter",
            "extra": "iterations: 2488889\ncpu: 339.00668129434456 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 313.45383096685157,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 337.96039455180335 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 311.7346299904893,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 302.3856161779293 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 15.973872767857904,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.043526785714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 18.497413558012678,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.833705525300942 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 18.49140820081492,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 18.462956414847177,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 18.487329117273024,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.415178448112645 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 19.55559928174605,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 19.670759104203206 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 18.823454632351055,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 18.477774272122687,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 18.510021593840897,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 2692.69871627032,
            "unit": "ns/iter",
            "extra": "iterations: 263529\ncpu: 2727.4038151398895 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 5358.394642857129,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 10622.178472417767,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 10672.385391136646 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 21503.193750000093,
            "unit": "ns/iter",
            "extra": "iterations: 32000\ncpu: 20996.09375 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 43399.637500002085,
            "unit": "ns/iter",
            "extra": "iterations: 16000\ncpu: 42968.75 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 95827.58805410299,
            "unit": "ns/iter",
            "extra": "iterations: 7467\ncpu: 96256.863532878 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 217251.31249999307,
            "unit": "ns/iter",
            "extra": "iterations: 3200\ncpu: 214843.75 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 506649.7999999911,
            "unit": "ns/iter",
            "extra": "iterations: 1000\ncpu: 500000 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 55.30753000000459,
            "unit": "ns/iter",
            "extra": "iterations: 10000000\ncpu: 54.6875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.455360842815246,
            "unit": "ns/iter",
            "extra": "iterations: 194782609\ncpu: 3.449358253538949 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.6534529999998995,
            "unit": "ns/iter",
            "extra": "iterations: 100000000\ncpu: 5.625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 11.072984375000594,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 10.986328125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 18.826467954286766,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.79882799911499 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 37.575181471868916,
            "unit": "ns/iter",
            "extra": "iterations: 18666667\ncpu: 36.8303564851722 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 72.7742075892847,
            "unit": "ns/iter",
            "extra": "iterations: 8960000\ncpu: 69.75446428571429 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 17.282949437837026,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 17.264229795105603 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.386469642857232,
            "unit": "ns/iter",
            "extra": "iterations: 56000000\ncpu: 13.113839285714286 ns\nthreads: 1"
          }
        ]
      },
      {
        "commit": {
          "author": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "committer": {
            "email": "alekseikutuzov2@yandex.com",
            "name": "Aleksei-Kutuzov",
            "username": "Aleksei-Kutuzov"
          },
          "distinct": true,
          "id": "434efc314c9ec5b569f9621922b52318c111f717",
          "message": "Merge branch 'master' of https://github.com/Aleksei-Kutuzov/PrismEngine",
          "timestamp": "2026-02-14T16:22:14+03:00",
          "tree_id": "753159f546cb8bca813ab0966640dda178df9fe5",
          "url": "https://github.com/ThePrismEngine/PrismEngine/commit/434efc314c9ec5b569f9621922b52318c111f717"
        },
        "date": 1771075420520,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "ECSBenchmark/CreateEntity",
            "value": 3.4801903062853405,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.376116065399793 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/DestroyEntity",
            "value": 272.67331249587914,
            "unit": "ns/iter",
            "extra": "iterations: 3200000\ncpu: 268.5546875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/AddComponent",
            "value": 311.5440250762725,
            "unit": "ns/iter",
            "extra": "iterations: 2635294\ncpu: 308.3147459069083 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RemoveComponent",
            "value": 301.4333545934006,
            "unit": "ns/iter",
            "extra": "iterations: 2508800\ncpu: 305.17578125 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetComponent",
            "value": 15.997861607143703,
            "unit": "ns/iter",
            "extra": "iterations: 44800000\ncpu: 16.043526785714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/64",
            "value": 18.435835878892224,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/128",
            "value": 18.39105284277757,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/256",
            "value": 18.43377070030087,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/512",
            "value": 18.358182243137037,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 17.64787934610795 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/1024",
            "value": 18.49336192973247,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 18.79882799911499 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/2048",
            "value": 18.484433200754115,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 17.99665194639868 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/4096",
            "value": 18.46349748628043,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWith_SingleComponent/8192",
            "value": 18.48524212933194,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/64",
            "value": 2663.3082142857183,
            "unit": "ns/iter",
            "extra": "iterations: 280000\ncpu: 2678.5714285714284 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/128",
            "value": 5351.371428571687,
            "unit": "ns/iter",
            "extra": "iterations: 112000\ncpu: 5301.339285714285 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/256",
            "value": 10522.301686152836,
            "unit": "ns/iter",
            "extra": "iterations: 74667\ncpu: 10672.385391136646 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/512",
            "value": 21418.547965874463,
            "unit": "ns/iter",
            "extra": "iterations: 34462\ncpu: 21763.101387034996 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/1024",
            "value": 43462.01874999878,
            "unit": "ns/iter",
            "extra": "iterations: 16000\ncpu: 42968.75 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/2048",
            "value": 94185.47991071336,
            "unit": "ns/iter",
            "extra": "iterations: 8960\ncpu: 94168.52678571429 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/4096",
            "value": 216289.756239105,
            "unit": "ns/iter",
            "extra": "iterations: 3446\ncpu: 217643.64480557168 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetEntitiesWithAll_TwoComponents/8192",
            "value": 507571.1000000069,
            "unit": "ns/iter",
            "extra": "iterations: 1000\ncpu: 515625 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/RegisterSystem",
            "value": 55.21880357143008,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 55.80357142857143 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/1",
            "value": 3.4772001723622328,
            "unit": "ns/iter",
            "extra": "iterations: 203636364\ncpu: 3.529575886554329 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/2",
            "value": 5.681694642857187,
            "unit": "ns/iter",
            "extra": "iterations: 112000000\ncpu: 5.719866071428571 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/4",
            "value": 10.992374999999832,
            "unit": "ns/iter",
            "extra": "iterations: 64000000\ncpu: 10.7421875 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/8",
            "value": 18.854528739772686,
            "unit": "ns/iter",
            "extra": "iterations: 37333333\ncpu: 18.41517873584981 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/16",
            "value": 37.37582611828928,
            "unit": "ns/iter",
            "extra": "iterations: 18666667\ncpu: 36.8303564851722 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/UpdateSystems/32",
            "value": 72.60850892856854,
            "unit": "ns/iter",
            "extra": "iterations: 11200000\ncpu: 71.14955357142857 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/SetResource",
            "value": 17.420095865490495,
            "unit": "ns/iter",
            "extra": "iterations: 40727273\ncpu: 17.264229795105603 ns\nthreads: 1"
          },
          {
            "name": "ECSBenchmark/GetResource",
            "value": 13.376983199210388,
            "unit": "ns/iter",
            "extra": "iterations: 49777778\ncpu: 13.497488779029068 ns\nthreads: 1"
          }
        ]
      }
    ]
  }
}