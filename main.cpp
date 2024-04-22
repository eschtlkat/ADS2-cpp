#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <string>
#include <vector>
#include <format>

struct result {
	int x, y, z;
};

std::vector<std::vector<result>> globalResults;
std::ofstream output("out.txt");

int steps = 1;

void findTriplets(const std::vector<int>& numbers, int depth, std::vector<bool> used, std::vector<result> results) {
	int sum = 0;
	for (int i = 0; i < numbers.size(); i++) {
		sum += numbers[i];
	}
	int numOfTriplets = numbers.size() / 3;

	for (int i = 0; i < numbers.size(); i++) {
		output << std::format("{:>8}) ", steps);
		steps++;
		for (int index = 1; index <= depth * 3 + 1; index++) {
			//printf("-");
			output << "-";
		}
		//printf("I trejeta talpinamas X%d: %d. [%d]. ",  i+1, numbers[i], numbers[i]);
		output << "I trejeta talpinamas X" << i + 1 << ": " << numbers[i] << ". [" << numbers[i] << "]. ";
		if (used[i]) {
			//printf("Yra panaudotas skaicius. \n");
			output << "Yra panaudotas skaicius. \n";
			continue;
		}
		//printf("Gilyn.\n");
		output << "Gilyn.\n";
		for (int j = i + 1; j < numbers.size(); j++) {
			output << std::format("{:>8}) ", steps);
            steps++;
            for (int index = 1; index <= depth * 3 + 2; index++) {
                //printf("-");
                output << "-";
            }
			//printf("I trejeta talpinamas X%d: %d. [%d, %d]. ", j+1, numbers[j], numbers[i], numbers[j]);
			output << "I trejeta talpinamas X" << j + 1 << ": " << numbers[j] << ". [" << numbers[i] << ", " << numbers[j] << "]. ";
			if (used[j]) {
				//printf("Yra panaudotas skaicius. \n");
				output << "Yra panaudotas skaicius. \n";
				continue;
			}
			//printf("Gilyn.\n");
			output << "Gilyn. \n";
			for (int k = j + 1; k < numbers.size(); k++) {
				output << std::format("{:>8}) ", steps);
				steps++;
                for (int index = 1; index <= depth * 3 + 3; index++) {
                    //printf("-");
                    output << "-";
                }
				//printf("I trejeta talpinamas X%d: %d. [%d, %d, %d]. ", k+1, numbers[k], numbers[i], numbers[j], numbers[k]);
				output << "I trejeta talpinamas X" << k + 1 << ": " << numbers[k] << ". [" << numbers[i] << ", " << numbers[j] << ", " << numbers[k]
						<< "]. ";
				if (used[k]) {
					//printf("Yra panaudotas skaicius.\n");
					output << "Yra panaudotas skaicius.\n";
					continue;
				}

				if (numbers[i] + numbers[j] + numbers[k] == sum / numOfTriplets) {
					//printf("Rasta. ");
					output << "Rasta. ";
					results.push_back({i, j, k});
					if (depth == numOfTriplets - 1) {
						//printf("Atgal. \n");
						output << "Atgal. \n";
						globalResults.push_back(results);
						return;
					}
					//printf("Gilyn. \n");
					output << "Gilyn. \n";
					used[i] = true;
					used[j] = true;
					used[k] = true;
					findTriplets(numbers, depth + 1, used, results);
					results.pop_back();
					used[i] = false;
					used[j] = false;
					used[k] = false;
				}
				else {
					//printf("Netinkama suma.\n");
					output << "Netinkama suma.\n";
				}
			}
		}
	}
}

int main() {
	std::cout << "Iveskite duomenu failo pavadinima\n";
	std::string inFileName;
	std::cin >> inFileName;
	std::ifstream input(inFileName);

	output << "2 uzduotis, 10 variantas. Laura Ukrinaite, 1 kursas, 5 grupe, 2 pogrupis.\n";
	output << "\n";
	output << "Salyga. Istirti, ar duotas N naturiniu skaiciu rinkinys gali buti suskirstytas i skaiciu trejetus taip, \n";
	output << "kad skaiciu visuose trejetuose suma butu vienoda.";
	output << "\n";

	output << "Sprendimo ideja:\n";
	output << "1) Suskirstyti N dydzio aibes skaicius i trejetus taip, kad visu trejetu suma butu vienoda.\n";
	output << "2) Skaiciu kiekis N turi dalytis is 3, kitaip nebus imanoma suskirstyti i trejetus.\n";
	output << "3) Visu trejetu suma turi dalytis is trejetu skaiciaus N/3, kitaip nebus imanoma suskirstyti taip, kad sumos butu vienodos.\n";
	output << "4) Programa pasiima viena skaiciu is duomenu rinkinio ir bando ji patalpinti i viena is nepilnu trejetu.\n";
	output << "5) Jeigu trejetas yra uzpildytas, programa patikrina, ar jo suma tinkama.\n";
	output << "6) Jeigu tinkama, tai programa isspausdina skaiciu trejeta. Panaudoti skaiciai pasizymimi kaip panaudoti.\n";
	output << "7) Jei netinkama, tai programa toliau eina per skaicius ir iesko kito skaiciaus trejeto.\n";
	output << "\n";

	output << "PIRMA DALIS\n";
	output << "Ivesties failas: " << inFileName << "\n";

	std::vector<int> numbers;
	for (int i; input >> i;) {
		numbers.push_back(i);
	}

	output << "DUOMENYS:\n";
	for (int i = 0; i < numbers.size(); i++) {
		output << "   s" << i + 1 << " = " << numbers[i] << "\n";
	}

	output << "Ivestas sprendiniu kiekis: " << numbers.size() << "\n";
	output << "Maximalus sprendiniu kiekis: 10\n";
	output << "\n";

	output << "ANTRA DALIS. Vykdymas\n";

	findTriplets(numbers, 0, std::vector<bool>(numbers.size(), false), std::vector<result>());

	int sumOfNumbers = 0;
	for (int i = 0; i < numbers.size(); i++) {
		sumOfNumbers += numbers[i];
	}

	sumOfNumbers /= (numbers.size() / 3);

	output << "\n";
	output << "TRECIA DALIS. Rezultatai.\n";
	output << "Bandymu skaicius: " << steps - 1 << ".\n";
	output << "Kiekvieno trejeto suma yra lygi: " << sumOfNumbers << ".\n";
	output << "Sprendiniai: \n";
	output << "\n";
	//std::cout << "numTriplets: " << globalResults.size() << "\n";
	int sprendinysNum = 1;
	for (auto& resVec : globalResults) {
		output << "Sprendinys: nr. " << sprendinysNum << ":\n";
		sprendinysNum++;
		for (auto& res : resVec) {
			output << "   s" << res.x + 1 << " s" << res.y + 1 << " s" << res.z + 1 << " : ";
			output << numbers[res.x] << " " << numbers[res.y] << " " << numbers[res.z] << "\n";
		}
	}
}