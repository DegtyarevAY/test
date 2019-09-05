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
������������ ��������� ��������� �� C++, ������� �� ����������� ��������� :
1. ��������� ���������� ����� ���������� �������������� ������ - ������, �������� � ���������� ��������. (����������
	����������� ����).������ ������ ������ ����� ����������� ���������� 3D - ����� � ������ �����������(3D
		������) �� ��������� t ����� ������.
	2. ��������� ���������(��������, ������ ��� ������) �������� ���� �����, ��������� ��������� �������, � �������
	��������� ���������.���������, ��� ��������� ����� ��������� ������� ���� �������������� �����.
	3. �������� ���������� ����� � ����������� ���� ������ � ���������� ��� t = PI / 4.
	4. ��������� ������ ���������, ������� ����� ��������� ������ ����� �� ������� ����������.���������, ���
	������ ��������� ���������(�� ���� �� ���������) ����� �������, ��������, � ������� ����������.
	5. ���������� ������ ��������� � ������� ����������� �������� �����������.�� ���� ������ ������� �����
	���������� ������, ��������� - ����������.
	6. ��������� ����� ����� �������� ���� ������ �� ������ ����������.
	�������������� �������������� ���������� :
7. ��������� ���������� �� ���������� ������ � ����������� ����, ������� ���������� API ���� ����������.

�������� � ����������:
1. ���������� ������ ������������ ����������� ������.
2. �� ����� �� ������ ������������ ������, �� ������ ������.
3. ������ ������ ���� ��������� ����������� (��������, ������� ������ ���� ��������������).
4. ���������� � ���������� ������ ���� ����������� � �������������� STL (C ++ Standard Template Library).
5. ���������� ����� ������������ ����������� C ++ 11 ��� ����.
6. ��� ������ ��������������� ����� ������������ �� ������ ������ (gcc, Visual C ++ � �. �.).
7. ��������� ������ ���� ��������� �� ����������� ����� ��� ����������� �� github. �������� ������ ��������� ������ �������� ���
(��� ���������������� �������� ������): * .h � * .cpp ����� � ����� �������, ��� ��� �� ����� �������������� ��������� � �������
����.

������ �����������:
- ��� ������ �������������� ����������, �� ���� ����� �������������� �� ��������� ������� C (t).
- ���� �������� ������� � ��������� XoY (�� ���� ��� Z-���������� ����� 0) � ������������ ��� ��������.
- ������ �������� ������� � ��������� XoY � ������������ ��� ����� ��������� ����� ���� X � Y.
- Helix �������� ���������������� � ������������ ��� �������� � ����� (��. ������� ����). ��������� 2 * PI �
��������������� ������������ ��� ����������, �.�. ����� ����� �� ������� ������������� ������� C (t + 2 * PI) = C (t) +
{0, 0, ���}.
*/
