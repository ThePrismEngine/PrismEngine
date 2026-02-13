window.BENCHMARK_DATA = {
  "lastUpdate": 1771011891160,
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
      }
    ]
  }
}