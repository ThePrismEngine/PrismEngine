#pragma once

namespace prism {
	namespace scene {
		struct Look {
			float x, y, z;
		};

		struct CameraComponent
		{
			bool isActive; // Рендерить ли
			Look look = { 0.0f, 0.0f, 0.0f }; // Взгляд

			float fovy = 45.0f;        // Угол обзора в градусах
			float aspect = 16.f / 9.f; // Соотношение сторон
			float zNear = 0.1f;        // Ближняя плоскость отсечения
			float zFar = 10.0f;        // Дальняя плоскость отсечения

			bool useСurrentWindowAspect = true; // Если истино то aspect игнорируется и соотношение камеры равно соотношению окна
		};
	}
}