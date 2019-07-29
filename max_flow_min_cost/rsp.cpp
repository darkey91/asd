#include <fstream>

int main() {
	std::fstream in("rps2.in");
	std::ofstream out("rps2.out");

	int r1, r2, s1, s2, p1, p2;
	in >> r1 >> s1  >> p1 >> r2 >> s2 >> p2;

	int rVSp = r1 - r2 - p2;
	int sVSr = s1 - s2 - r2;
	int pVSs = p1 - p2 - s2;
	out << std::max(0, std::max(rVSp, std::max(sVSr, pVSs)));
	return 0;
}
