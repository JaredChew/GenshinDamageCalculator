#include <iostream>
#include <sstream>
#include <iomanip>

#define DECIMAL_PRECISION 3

float decimalPrecisionRoundOff(float value, const int& decimals) {

	std::ostringstream ss;

	ss << std::fixed << std::setprecision(decimals) << value;

	std::string s = ss.str();

	if (decimals > 0 && s[s.find_last_not_of('0')] == '.') {
		s.erase(s.size() - decimals + 1);
	}

	return std::stof(s);

}

float res(const float& baseRES, const float& bonusRES, const float& resReduc) {

	float resInitial = (baseRES + bonusRES - resReduc) / 100.0f;

	if (resInitial < 0.0f) {

		return 1.0f + (abs(resInitial) / 2.0f);

	}
	else if (resInitial > 75.0f) {

		return 1.0f / (4.0f * resInitial + 1.0f);

	}

	return 1.0f - resInitial;

}

int main() {

	//init

	int playerLevel = 90;

	// ! for precision of +- 1

	int attack = 2633;
	float talent = 170.0f;
	float bonusDMG = 61.6f + 12.0f + 28.0f;
	float critDMG = 175.2f;
	//float vapeMelt = 1.0f; // unfreeze to use, that inclused the ones below

	// ! for near perfect precision
	int baseATK = 997; //white damage
	int additionalATK = 311 + 16 + 33 + 16;
	float attackPCNT = 46.6f + 18.6f + 11.6f + 15.2f + 18.1f + 17.5f;
	int totalAttack = baseATK + ((attackPCNT / 100.0f) * baseATK + additionalATK); //Don't touch
	//attack = totalAttack; // unfreeze to use near perfection calculation

	// !! BENNET BUFF !! //
	//attack += 951; // unfreeze to use

	int enemyLevel = 90;
	float enemyRes = 10.0f;
	float enemyResReduc = 0.0f;
	float enemyDefReduc = 0.0f;

	//conversion

	talent /= 100.0f;
	bonusDMG = 1.0f + (bonusDMG / 100.0f);
	critDMG = 1.0f + (critDMG / 100.0f);
	enemyDefReduc = (enemyDefReduc / 100.0f);
	//vapeMelt = 1.0f + (vapeMelt / 100.0f);

	//calculation

	float rawDamage = attack * talent * critDMG * bonusDMG;// *vapeMelt;

	float enemyResActual = res(enemyRes, 0.0f, enemyResReduc);
	float enemyDef = (playerLevel + 100.0f) / ((1.0f - enemyDefReduc) * (enemyLevel + 100.0f) + (playerLevel + 100.0f));

	float actualDamage = rawDamage * enemyDef * enemyResActual;

	//conclusion

	std::cout << "Attack stat: " << attack << "\n";
	std::cout << "Raw Damage: " << rawDamage << "\n";
	std::cout << "Enemy Defense Reduction: " << enemyDef << "\n";
	std::cout << "Enemy Resistance Actual: " << enemyResActual << "\n";
	std::cout << "Actual Damage: " << actualDamage << "\n";
	
	std::cin.get();

	return 0;

	//Deprecated

	//float actualDamage_decimalPrecision = decimalPrecisionRoundOff(rawDamage, DECIMAL_PRECISION) * decimalPrecisionRoundOff(enemyDef, DECIMAL_PRECISION) * decimalPrecisionRoundOff(enemyResActual, DECIMAL_PRECISION);
	//float correctedDamage = (pow(actualDamage, 2) / actualDamage_decimalPrecision);

	//std::cout << "Actual Damage Decimal Precision: " << actualDamage_decimalPrecision << "\n";
	//std::cout << "Correction: " << correctedDamage << "\n";

}