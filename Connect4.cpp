#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Stablo {
	struct Elem {
		int br;
		int zauzeto = 0;
		Elem* roditelj, *brat;
		Elem** pokazivaci;
		int mat[5][5];
		Elem(int brr = 0, Elem* roditeljj = nullptr, Elem* bratt = nullptr) {
			br = brr;
			roditelj = roditeljj;
			pokazivaci = new Elem*[5];
			brat = bratt;
		}
		~Elem() {
			delete[] pokazivaci;
			pokazivaci = nullptr;
		}
	};
	Elem* koren;
	Elem *posl;
	Elem* levi = nullptr;
public:
	Stablo() {
		koren = nullptr;
		posl = nullptr;
    }

	~Stablo();
	Stablo(const Stablo&) = delete;
	Stablo& operator=(const Stablo&) = delete;
	Stablo& dodaj(int mat[5][5]);
	void ispisi();

};


int koigraprvi(int matrica[5][5]) {
	srand(time(NULL));
	int c = 0, p = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			if (matrica[i][j] == 1)c++;
			else if (matrica[i][j] == 2)p++;
		}
	if (c < p)return 1;
	else if (c > p)return 2;
	else if ((rand() / (double)RAND_MAX + 1) >= 1.5)return 2;
	else return 1;
}
int kojepobedio(int matrica[5][5]) {
	int p = 0; int b = 0; int zapamti = 0;
	for (int i = 4; i >= 0; i--) {
		for (int j = 0; j < 5; j++) {
			if (matrica[i][j] == 1) { zapamti = 1; b++; p = 0; if (b == 3)return 1; }
			else if (matrica[i][j] == 2) { zapamti = 2; p++; b = 0; if (p == 3)return -1; }
			else { p = 0; b = 0; zapamti = 0; }
		}
		p = 0; b = 0; zapamti = 0;
	}
	for (int j = 0; j < 5; j++) {
		for (int i = 4; i >= 0; i--) {
			if (matrica[i][j] == 1) { zapamti = 1; b++; p = 0; if (b == 3)return 1; }
			else if (matrica[i][j] == 2) { zapamti = 2; p++; b = 0; if (p == 3)return -1; }
			else { p = 0; b = 0; zapamti = 0; break; }

		}
		p = 0; b = 0; zapamti = 0;

	}
	for (int i = 4; i >= 2; i--) {
		for (int j = 0; j < 3; j++) {
			if (matrica[i][j] == matrica[i - 1][j + 1] && matrica[i][j] == matrica[i - 2][j + 2])if (matrica[i][j] != 0) {
				if (matrica[i][j] == 2) return -1; return 1;
			}

		}
	}
	for (int i = 4; i >= 2; i--) {
		for (int j = 4; j >= 2; j--) {
			if (matrica[i][j] == matrica[i - 1][j - 1] && matrica[i][j] == matrica[i - 2][j - 2]) if (matrica[i][j] != 0) {
				if (matrica[i][j] == 2) return -1; return 1;
			}
		}
	}
	int k = 0;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (matrica[i][j] != 0)
				k++;
	if (k == 25)
		return 0;
	return 5;

}
bool ubaci(int matrica[5][5], int broj, int kolona) {
	if (kolona > 4 || kolona < 0) { cout << kolona; int x; cin >> x; exit(1); };
	int pun = 0;
	for (int i = 0; i < 5; i++) {
		if (matrica[0][i] != 0)pun++;
	}
	if (pun == 5)  return false;
	bool b = false; int brojac = 0;
	for (int i = 0; i < 5; i++) {
		if (matrica[i][kolona] == 0) {
			brojac++; continue;
		}
		else {
			if (i - 1 == -1) return false;
			else { matrica[i - 1][kolona] = broj; b = true; break; }
		}
	}
	if (brojac == 5) {
		matrica[4][kolona] = broj; b = true;
	}

	return b;
}
void kopiraj(int gde[5][5], int odakle[5][5]) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)gde[i][j] = odakle[i][j];
}


Stablo::~Stablo()
{
	Elem *tek, *stari, *levi = nullptr;
	bool kraj = false;
	int m = 0;
	int imalevi = 0;
	tek = koren;
	while (kraj == false) {
		if (m != 5)
			if ((tek->pokazivaci[m]) == nullptr) m++;
			else {
				if (imalevi == 0) {
					levi = tek->pokazivaci[m]; imalevi = 1;
				}
				tek->pokazivaci[m]->roditelj = nullptr;
				tek->pokazivaci[m] = nullptr;
				m++;
			}
		else if (m == 5) {
			if (tek->brat != nullptr) {
				stari = tek; tek = tek->brat; delete stari; m = 0;
			}
			else {
				if (imalevi == 1) {
					stari = tek; tek = levi; imalevi = 0; m = 0; delete stari;
				}
				else if (imalevi == 0) {
					delete tek; kraj = true;
				}
			}
		}
	}
}


Stablo& Stablo::dodaj(int matrica[5][5]) {

	Elem* levi = nullptr;
	Elem *tek, *privremeni, *trenutni;
	int koigra = koigraprvi(matrica); bool nemalevi = 0;
	int r = 0; bool kraj = false;
	while (kraj == false) {
		Elem* novi = new Elem();
		if (koren == nullptr) {
			koren = novi;
			posl = novi;
			kopiraj(novi->mat, matrica);
		}
		else if (koren == posl) {
			posl->pokazivaci[posl->zauzeto] = novi;
			kopiraj(novi->mat, koren->mat);
			if (ubaci(novi->mat, koigra, koren->zauzeto) == false) {
				koren->pokazivaci[koren->zauzeto] = nullptr;
			}
			else {
				novi->roditelj = koren; posl = novi; levi = novi;
				novi->br = kojepobedio(novi->mat);
				if ((novi->br) == 1 || (novi->br) == -1) {
					for (int i = 0; i < 5; i++) novi->pokazivaci[i] = nullptr;
					novi->zauzeto = 5;
				}
				if (novi->br != 5) {
					int promena = koigra;
					Elem* pom = novi;
					while (pom != koren) {
						if (pom->roditelj->br == 5)pom->roditelj->br = pom->br;
						else {
							if (promena == 2 && (pom->roditelj->br > pom->br))pom->roditelj->br = pom->br;
							else if (promena == 1 && (pom->roditelj->br < pom->br))pom->roditelj->br = pom->br;
							pom = pom->roditelj;
							if (promena == 1) promena = 2;
							else promena = 1;
						}
					}
				}
			}
			(koren->zauzeto)++;
		}
		else if (koren != posl) {
			tek = posl->roditelj;
			if (tek->zauzeto != 5) {
				tek->pokazivaci[tek->zauzeto] = novi;
				kopiraj(novi->mat, tek->mat);
				if (ubaci(novi->mat, koigra, tek->zauzeto) == false)
					tek->pokazivaci[tek->zauzeto] = nullptr;
				else {
					novi->roditelj = tek;
					if (nemalevi == 1) { levi = novi; nemalevi = 0; }
					else posl->brat = novi;
					posl = novi;
					(novi->br) = kojepobedio(novi->mat);
					if ((novi->br) == 1 || (novi->br) == -1) {
						for (int i = 0; i < 5; i++)
							novi->pokazivaci[i] = nullptr;
						novi->zauzeto = 5;
					}
					if (novi->br != 5) {
						int promena = koigra;
						Elem* pom = novi;
						while (pom != koren) {
							if (pom->roditelj->br == 5)pom->roditelj->br = pom->br;
							else {
								if (promena == 2 && (pom->roditelj->br > pom->br))pom->roditelj->br = pom->br;
								else if (promena == 1 && (pom->roditelj->br < pom->br))pom->roditelj->br = pom->br;
								pom = pom->roditelj;
								if (promena == 1) promena = 2;
								else promena = 1;
							}
						}
					}

				}
				(tek->zauzeto)++;
			}

			else if ((tek->zauzeto) == 5) {
				if ((tek->brat) != nullptr && (tek->brat->zauzeto) != 5) {
					tek = tek->brat; tek->pokazivaci[tek->zauzeto] = novi;
					kopiraj(novi->mat, tek->mat);
					if (ubaci(novi->mat, koigra, tek->zauzeto) == false)
						tek->pokazivaci[tek->zauzeto] = nullptr;
					else {
						novi->roditelj = tek;
						if (nemalevi == 1) { levi = novi; nemalevi = 0; }
						else posl->brat = novi;
						posl = novi;
						(novi->br) = kojepobedio(novi->mat);
						if ((novi->br) == 1 || (novi->br) == -1) {
							for (int i = 0; i < 5; i++) novi->pokazivaci[i] = nullptr;
							novi->zauzeto = 5;
						}
						if (novi->br != 5) {
							int promena = koigra;
							Elem* pom = novi;
							while (pom != koren) {
								if (pom->roditelj->br == 5)pom->roditelj->br = pom->br;
								else {
									if (promena == 2 && (pom->roditelj->br > pom->br))pom->roditelj->br = pom->br;
									else if (promena == 1 && (pom->roditelj->br < pom->br))pom->roditelj->br = pom->br;
									pom = pom->roditelj;
									if (promena == 1) promena = 2;
									else promena = 1;
								}
							}
						}
					}
					(tek->zauzeto)++;
				}
				else if (tek->brat == nullptr) {
					if ((levi->zauzeto) != 5) {
						tek = levi;
						if (nemalevi == 0) {
							if (koigra == 1) koigra = 2;
							else koigra = 1;
						}
						tek->pokazivaci[tek->zauzeto] = novi;
						kopiraj(novi->mat, tek->mat);
						if (ubaci(novi->mat, koigra, tek->zauzeto) == false)
						{
							tek->pokazivaci[tek->zauzeto] = nullptr; nemalevi = 1;
						}
						else {
							novi->roditelj = tek; posl = novi; levi = novi;
							nemalevi = 0;
							(novi->br) = kojepobedio(novi->mat);
							if ((novi->br) == 1 || (novi->br) == -1) {
								for (int i = 0; i < 5; i++) novi->pokazivaci[i] = nullptr;
								novi->zauzeto = 5;
							}
							if (novi->br != 5) {
								int promena = koigra;
								Elem* pom = novi;
								while (pom != koren) {
									if (pom->roditelj->br == 5)pom->roditelj->br = pom->br;
									else {
										if (promena == 2 && (pom->roditelj->br > pom->br))pom->roditelj->br = pom->br;
										else if (promena == 1 && (pom->roditelj->br < pom->br))pom->roditelj->br = pom->br;
										pom = pom->roditelj;
										if (promena == 1) promena = 2;
										else promena = 1;
									}
								}
							}
						}
						(tek->zauzeto)++;
					}
					else if ((levi->zauzeto) == 5)
					{
						privremeni = levi;
						while (privremeni != nullptr) {
							if (privremeni->zauzeto != 5) {
								r = 1; break;
							}
							else {
								privremeni = privremeni->brat;
							}
						}

						if (r == 0) kraj = true;
						if (r == 1) {
							tek = privremeni; r = 0;
							if (nemalevi == 0) {
								if (koigra == 1) koigra = 2;
								else koigra = 1;
							}
							tek->pokazivaci[tek->zauzeto] = novi;
							kopiraj(novi->mat, tek->mat);
							if (ubaci(novi->mat, koigra, tek->zauzeto) == false)
							{
								tek->pokazivaci[tek->zauzeto] = nullptr; nemalevi = 1;
							}
							else {
								novi->roditelj = tek; posl = novi; levi = novi;
								nemalevi = 0;
								(novi->br) = kojepobedio(novi->mat);
								if ((novi->br) == 1 || (novi->br) == -1) {
									for (int i = 0; i < 5; i++) novi->pokazivaci[i] = nullptr;
									novi->zauzeto = 5;
								}
								if (novi->br != 5) {
									int promena = koigra;
									Elem* pom = novi;
									while (pom != koren) {
										if (pom->roditelj->br == 5)pom->roditelj->br = pom->br;
										else {
											if (promena == 2 && (pom->roditelj->br > pom->br))pom->roditelj->br = pom->br;
											else if (promena == 1 && (pom->roditelj->br < pom->br))pom->roditelj->br = pom->br;
											pom = pom->roditelj;
											if (promena == 1) promena = 2;
											else promena = 1;
										}
									}
								}
							}
							(tek->zauzeto)++;

						}
					}

				}
				else if ((tek->brat->zauzeto) == 5) {
					privremeni = tek->brat; int y = 0;
					while ((privremeni != nullptr) && (privremeni->zauzeto == 5)) {
						tek = privremeni;
						privremeni = privremeni->brat;
					}
					if (privremeni == nullptr) {
						y = 1;
						if ((levi->zauzeto) != 5) {
							tek = levi;
							if (nemalevi == 0) {
								if (koigra == 1) koigra = 2;
								else koigra = 1;
							}
							tek->pokazivaci[tek->zauzeto] = novi;
							kopiraj(novi->mat, tek->mat);
							if (ubaci(novi->mat, koigra, tek->zauzeto) == false)
							{
								tek->pokazivaci[tek->zauzeto] = nullptr; nemalevi = 1;
							}
							else {
								novi->roditelj = tek; posl = novi; levi = novi;
								nemalevi = 0;
								(novi->br) = kojepobedio(novi->mat);
								if ((novi->br) == 1 || (novi->br) == -1) {
									for (int i = 0; i < 5; i++) novi->pokazivaci[i] = nullptr;
									novi->zauzeto = 5;
								}
								if (novi->br != 5) {
									int promena = koigra;
									Elem* pom = novi;
									while (pom != koren) {
										if (pom->roditelj->br == 5)pom->roditelj->br = pom->br;
										else {
											if (promena == 2 && (pom->roditelj->br > pom->br))pom->roditelj->br = pom->br;
											else if (promena == 1 && (pom->roditelj->br < pom->br))pom->roditelj->br = pom->br;
											pom = pom->roditelj;
											if (promena == 1) promena = 2;
											else promena = 1;
										}
									}
								}
							}
							(tek->zauzeto)++;
						}
						else if ((levi->zauzeto) == 5)
						{
							privremeni = levi;
							while (privremeni != nullptr) {
								if (privremeni->zauzeto != 5) {
									r = 1; break;
								}
								else {
									privremeni = privremeni->brat;
								}
							}

							if (r == 0) kraj = true;
							if (r == 1) {
								tek = privremeni; r = 0;
								if (nemalevi == 0) {
									if (koigra == 1) koigra = 2;
									else koigra = 1;
								}
								tek->pokazivaci[tek->zauzeto] = novi;
								kopiraj(novi->mat, tek->mat);
								if (ubaci(novi->mat, koigra, tek->zauzeto) == false)
								{
									tek->pokazivaci[tek->zauzeto] = nullptr; nemalevi = 1;
								}
								else {
									novi->roditelj = tek; posl = novi; levi = novi;
									nemalevi = 0;
									(novi->br) = kojepobedio(novi->mat);
									if ((novi->br) == 1 || (novi->br) == -1) {
										for (int i = 0; i < 5; i++) novi->pokazivaci[i] = nullptr;
										novi->zauzeto = 5;
									}
									if (novi->br != 5) {
										int promena = koigra;
										Elem* pom = novi;
										while (pom != koren) {
											if (pom->roditelj->br == 5)pom->roditelj->br = pom->br;
											else {
												if (promena == 2 && (pom->roditelj->br > pom->br))pom->roditelj->br = pom->br;
												else if (promena == 1 && (pom->roditelj->br < pom->br))pom->roditelj->br = pom->br;
												pom = pom->roditelj;
												if (promena == 1) promena = 2;
												else promena = 1;
											}
										}
									}
								}
								(tek->zauzeto)++;

							}
						}
					}
					else tek = privremeni;
					if (y == 0) {
						tek->pokazivaci[tek->zauzeto] = novi;
						kopiraj(novi->mat, tek->mat);
						if (ubaci(novi->mat, koigra, tek->zauzeto) == false)
							tek->pokazivaci[tek->zauzeto] = nullptr;
						else {
							novi->roditelj = tek; posl->brat = novi;
							posl = novi;
							if (nemalevi == 1) { levi = novi; nemalevi = 0; }
							(novi->br) = kojepobedio(novi->mat);
							if ((novi->br) == 1 || (novi->br) == -1) {
								for (int i = 0; i < 5; i++) novi->pokazivaci[i] = nullptr;
								novi->zauzeto = 5;
							}
							if (novi->br != 5) {
								int promena = koigra;
								Elem* pom = novi;
								while (pom != koren) {
									if (pom->roditelj->br == 5)pom->roditelj->br = pom->br;
									else {
										if (promena == 2 && (pom->roditelj->br > pom->br))pom->roditelj->br = pom->br;
										else if (promena == 1 && (pom->roditelj->br < pom->br))pom->roditelj->br = pom->br;
										pom = pom->roditelj;
										if (promena == 1) promena = 2;
										else promena = 1;
									}
								}
							}

						}
						(tek->zauzeto)++;

					}
				}
			}
		}

	}
	return *this;
}

void Stablo::ispisi() {
	Elem *tek, *levi = nullptr;
	tek = koren;
	int imalevi=0;
	int m = 0;
	bool kraj = false;
	while (kraj == false) {
		if (m != 5) {
			if (m == 0) cout << "(";
			if (tek->pokazivaci[m] == nullptr) cout << "/";
			else {
				cout << tek->pokazivaci[m]->br;
				if (imalevi == 0) {
					imalevi = 1; levi = tek->pokazivaci[m];
				}
			}
			if (m != 4) cout << ",";
			else if (m == 4) cout << ")";
			m++;
		}
		else if (m == 5) {
			if (tek->brat != nullptr) {
				tek = tek->brat; m = 0; cout << " ";
			}
			else if (tek->brat == nullptr) {
				if (imalevi == 1) {
					cout << endl; tek = levi; imalevi = 0; m = 0;
				}
				else  if (imalevi==0 ) kraj = true;
			}

		}
	}

}

int main() {
	Stablo s;
	int matrica[5][5];
	int izbor;
	bool end = false;
	while (end==false) {
		cout << "1)Zapocnite novu igru\n"
			    "2)Napravite stablo\n"
			    "3)Ispisite stablo\n"
			    "4)Kraj igre\n";
			    
		cin >> izbor;
		switch (izbor) {
		case 1:cout << "Unesite pocetno stanje igre" << endl<<"oznake: 1(crvena), 2(plava), 0(prazno)" << endl;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					cin >> matrica[i][j];
					if (matrica[i][j] != 2 && matrica[i][j] != 0 && matrica[i][j] != 1) { --j; }
				}
			}
			cout << endl << "Pobednik igre je:" << kojepobedio(matrica) << endl;
			break;
		case 2: s.dodaj(matrica); break;
		case 3:cout << endl; s.ispisi();
			break;
		case 4:end = true; cout << "KRAJ IGRE!"; break;
		default: cout << "UNELI STE POGRESAN BROJ!"; break;
		
		}
	}
	return 0;
}