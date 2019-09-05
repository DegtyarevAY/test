#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"

using namespace std;

const double eps = 0.00001;
const double pi = 3.141592;
enum shape_t { circle_t, ellipse_t, helix_t };

inline double gen_double(double min, double max)
{
	std::random_device rd;
	std::uniform_real_distribution<double> dis{ min, max };
	return dis(rd);
}

void Generate_shapes(vector<shared_ptr<Shape>>& shapes, int size, double min, double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(circle_t, helix_t);

	for (int i = 0; i < size; ++i)
	{
		switch (dis(rd))
		{
		case circle_t:
		{
			auto sh_p = make_shared<Circle>(Point(gen_double(min, max), gen_double(min, max), 0),
				gen_double(eps, max));
			shapes.push_back(sh_p);
			break;
		}

		case ellipse_t:
		{
			auto sh_p = make_shared<Ellipse>(Point(gen_double(min, max), gen_double(min, max), 0),
				gen_double(eps, max), gen_double(eps, max));
			shapes.push_back(sh_p);
			break;
		}
		case helix_t:
		{
			auto sh_p = make_shared<Helix>(Point(gen_double(min, max), gen_double(min, max), 0),
				gen_double(eps, max), gen_double(eps, max));
			shapes.push_back(sh_p);
			break;
		}
		default:
			break;
		}
	}
}

int main()
{
	vector<shared_ptr<Shape>> shape_vec;
	vector<shared_ptr<Circle>> circle_vec;
	double min = -10;
	double max = 10;
	int size = 20;
	double rad_sum = 0;

	Generate_shapes(shape_vec, size, min, max);

	for (auto& ps : shape_vec)
	{
		cout << type_index(typeid(*ps)).name() << endl;
		cout << "-->  Point(" << ps->get_point(pi / 4).x << ", " << ps->get_point(pi / 4).y << ", "
			<< ps->get_point(pi / 4).z << ")";
		cout << endl;

		if (typeid(*ps).hash_code() == typeid(Circle).hash_code())
		{
			circle_vec.push_back(dynamic_pointer_cast<Circle>(ps));
		}
	}
	sort(circle_vec.begin(), circle_vec.end(), [](const auto& lh, const auto& rh)
	{
		return lh->get_radius() < rh->get_radius();
	});
	for_each(circle_vec.begin(), circle_vec.end(), [&rad_sum](const auto& c)
	{
		rad_sum += c->get_radius();
	});

	cout << endl;
	for (auto& pc : circle_vec)
	{
		cout << type_index(typeid(*pc)).name() << endl;
		cout << "-->  Point(" << pc->get_point(pi / 4).x << ", " << pc->get_point(pi / 4).y << ", "
			<< pc->get_point(pi / 4).z << ")" << "Radius " << pc->get_radius();
		cout << endl;
	}
	cout << "Radius sum = " << rad_sum << endl;
	system("pause");
}

/*
Разработайте небольшую программу на C++, которая бы реализовала следующее :
1. Поддержка нескольких типов трехмерных геометрических кривых - кругов, эллипсов и трехмерных спиралей. (Упрощенный
	определения ниже).Каждая кривая должна иметь возможность возвращать 3D - точку и первую производную(3D
		вектор) по параметру t вдоль кривой.
	2. Заполните контейнер(например, вектор или список) объектов этих типов, созданных случайным образом, с помощью
	случайные параметры.Убедитесь, что контейнер будет содержать объекты всех поддерживаемых типов.
	3. Выведите координаты точек и производных всех кривых в контейнере при t = PI / 4.
	4. Заполните второй контейнер, который будет содержать только круги из первого контейнера.Убедитесь, что
	второй контейнер разделяет(то есть не клонирует) круги первого, например, с помощью указателей.
	5. Сортируйте второй контейнер в порядке возрастания радиусов окружностей.То есть первый элемент имеет
	наименьший радиус, последний - наибольший.
	6. Вычислите общую сумму радиусов всех кривых во втором контейнере.
	Дополнительные необязательные требования :
7. Разделите реализацию на библиотеку кривых и исполняемый файл, который использует API этой библиотеки.

Ожидания к реализации:
1. Реализация должна использовать виртуальные методы.
2. Не имеет ни явного освобождения памяти, ни утечек памяти.
3. Кривые должны быть физически правильными (например, радиусы должны быть положительными).
4. Контейнеры и сортировка должны быть реализованы с использованием STL (C ++ Standard Template Library).
5. Реализация может использовать конструкции C ++ 11 или выше.
6. Код должен компилироваться любым компилятором по вашему выбору (gcc, Visual C ++ и т. Д.).
7. Результат должен быть отправлен по электронной почте или опубликован на github. Доставка должна содержать только исходный код
(без скомпилированных двоичных файлов): * .h и * .cpp файлы и файлы проекта, так что мы можем скомпилировать результат с помощью
сами.

Кривые определения:
- Все кривые параметрически определены, то есть точка рассчитывается по некоторой формуле C (t).
- Круг является плоским в плоскости XoY (то есть все Z-координаты равны 0) и определяется его радиусом.
- Эллипс является плоским в плоскости XoY и определяется его двумя радиусами вдоль осей X и Y.
- Helix является пространственным и определяется его радиусом и шагом (см. Рисунок ниже). Требуется 2 * PI в
параметрическое пространство для округления, т.е. любая точка на спирали удовлетворяет условию C (t + 2 * PI) = C (t) +
{0, 0, шаг}.
*/
