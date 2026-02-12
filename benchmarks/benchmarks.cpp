#include <benchmark/benchmark.h>
#include <PrismEngineECS.h>
#include <memory>
#include <vector>
#include <random>

using namespace prism::scene;

// ----------------------------------------------------------------------------
//  Тестовые компоненты (минимальные POD-типы)
// ----------------------------------------------------------------------------
struct Position_ { float x{}, y{}, z{}; };
struct Velocity_ { float dx{}, dy{}, dz{}; };
struct Health_ { int hp{ 100 }; };
struct Renderable_ { uint32_t mesh{}, material{}; };

// ----------------------------------------------------------------------------
//  Тестовая система (ничего не делает, измеряются накладные расходы вызова)
// ----------------------------------------------------------------------------
class MockSystem : public ISystem {
public:
    void update() override {
        // пусто – только издержки диспетчеризации
    }
};

// ----------------------------------------------------------------------------
//  Фикстура: создаёт сцену и по требованию генерирует сущности с компонентами
// ----------------------------------------------------------------------------
class ECSBenchmark : public benchmark::Fixture {
public:
    void SetUp(const ::benchmark::State&) override {
        scene = std::make_unique<Scene>();

        // Принудительная регистрация компонентов (если ECS требует явной регистрации)
        // Создаём фиктивную сущность, добавляем по одному компоненту каждого типа,
        // чтобы внутренние структуры ComponentManager инициализировались.
        Entity dummy = scene->createEntity();
        scene->addComponent(dummy, Position_{});
        scene->addComponent(dummy, Velocity_{});
        scene->addComponent(dummy, Health_{});
        scene->addComponent(dummy, Renderable_{});
        scene->destroyEntity(dummy);
    }

    void TearDown(const ::benchmark::State&) override {
        scene.reset();
    }

    // Создаёт заданное количество сущностей, каждая получает компонент Position
    std::vector<Entity> createEntitiesWithPosition(size_t count) {
        std::vector<Entity> entities;
        entities.reserve(count);
        for (size_t i = 0; i < count; ++i) {
            Entity e = scene->createEntity();
            scene->addComponent(e, Position_{ 1.0f, 2.0f, 3.0f });
            entities.push_back(e);
        }
        return entities;
    }

    // Создаёт сущности с компонентами Position и Velocity
    std::vector<Entity> createEntitiesWithPositionVelocity(size_t count) {
        std::vector<Entity> entities;
        entities.reserve(count);
        for (size_t i = 0; i < count; ++i) {
            Entity e = scene->createEntity();
            scene->addComponent(e, Position_{});
            scene->addComponent(e, Velocity_{});
            entities.push_back(e);
        }
        return entities;
    }

protected:
    std::unique_ptr<Scene> scene;
};

// ============================================================================
//  Бенчмарки создания / удаления сущностей (без параметров)
// ============================================================================

BENCHMARK_F(ECSBenchmark, CreateEntity)(benchmark::State& state) {
    for (auto _ : state) {
        Entity e = scene->createEntity();
        benchmark::DoNotOptimize(e);
    }
}

BENCHMARK_F(ECSBenchmark, DestroyEntity)(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        Entity e = scene->createEntity();
        state.ResumeTiming();

        scene->destroyEntity(e);
    }
}

// ============================================================================
//  Бенчмарки операций с компонентами (без параметров)
// ============================================================================

BENCHMARK_F(ECSBenchmark, AddComponent)(benchmark::State& state) {
    Entity e = scene->createEntity();
    for (auto _ : state) {
        scene->addComponent(e, Velocity_{});
        state.PauseTiming();
        scene->removeComponent<Velocity_>(e);
        state.ResumeTiming();
    }
}

BENCHMARK_F(ECSBenchmark, RemoveComponent)(benchmark::State& state) {
    Entity e = scene->createEntity();
    for (auto _ : state) {
        state.PauseTiming();
        scene->addComponent(e, Velocity_{});
        state.ResumeTiming();

        scene->removeComponent<Velocity_>(e);
    }
}

BENCHMARK_F(ECSBenchmark, GetComponent)(benchmark::State& state) {
    Entity e = scene->createEntity();
    scene->addComponent(e, Health_{});
    for (auto _ : state) {
        Health_* h = scene->getComponent<Health_>(e);
        benchmark::DoNotOptimize(h);
    }
}

// ============================================================================
//  Бенчмарки запросов множеств сущностей (параметризованные)
// ============================================================================

BENCHMARK_DEFINE_F(ECSBenchmark, GetEntitiesWith_SingleComponent)
(benchmark::State& state) {
    const size_t numEntities = state.range(0);
    createEntitiesWithPosition(numEntities);

    for (auto _ : state) {
        auto& entities = scene->getEntitiesWith<Position_>();
        benchmark::DoNotOptimize(entities);
    }
}
BENCHMARK_REGISTER_F(ECSBenchmark, GetEntitiesWith_SingleComponent)
->RangeMultiplier(2)->Range(64, 8 << 10);

// ----------------------------------------------------------------------------

BENCHMARK_DEFINE_F(ECSBenchmark, GetEntitiesWithAll_TwoComponents)
(benchmark::State& state) {
    const size_t numEntities = state.range(0);
    createEntitiesWithPositionVelocity(numEntities);

    for (auto _ : state) {
        auto entities = scene->getEntitiesWithAll<Position_, Velocity_>();
        benchmark::DoNotOptimize(entities);
    }
}
BENCHMARK_REGISTER_F(ECSBenchmark, GetEntitiesWithAll_TwoComponents)
->RangeMultiplier(2)->Range(64, 8 << 10);

// ============================================================================
//  Бенчмарки систем
// ============================================================================

BENCHMARK_F(ECSBenchmark, RegisterSystem)(benchmark::State& state) {
    for (auto _ : state) {
        SystemId sid = scene->registerSystem<MockSystem>();
        benchmark::DoNotOptimize(sid);
        // Система останется зарегистрированной, но каждый тест запускается
        // на новой фикстуре (SetUp/TearDown), поэтому переполнения не будет.
    }
}

// ----------------------------------------------------------------------------

BENCHMARK_DEFINE_F(ECSBenchmark, UpdateSystems)
(benchmark::State& state) {
    const int numSystems = state.range(0);
    for (int i = 0; i < numSystems; ++i) {
        scene->registerSystem<MockSystem>();
    }

    for (auto _ : state) {
        scene->update();
    }
}
BENCHMARK_REGISTER_F(ECSBenchmark, UpdateSystems)
->RangeMultiplier(2)->Range(1, 32);

// ============================================================================
//  Бенчмарки глобальных ресурсов (без параметров)
// ============================================================================

BENCHMARK_F(ECSBenchmark, SetResource)(benchmark::State& state) {
    for (auto _ : state) {
        scene->setResource(Health_{});
    }
}

BENCHMARK_F(ECSBenchmark, GetResource)(benchmark::State& state) {
    scene->setResource(Health_{});
    for (auto _ : state) {
        Health_* h = scene->getResource<Health_>();
        benchmark::DoNotOptimize(h);
    }
}


BENCHMARK_MAIN();