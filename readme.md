# Studentų Analizė

Programa skirta studentų duomenų nuskaitymui, rūšiavimui ir skirstymui į dvi grupes: **kietiakus** (galutinis ≥ 5.0) ir **vargšiukus** (galutinis < 5.0).

## Diegimo instrukcija

**Reikalavimai**
* C++17 palaikantis kompiliatorius (`g++ 9+` arba `clang++ 9+`, `MSVC`)
* `make` (Unix) arba `cmake 3.16+` (bet kuri OS)

**Su Make (Unix)**
```bash
git clone [https://github.com/jusu-vartotojas/studentu-analize.git](https://github.com/jusu-vartotojas/studentu-analize.git)
cd studentu-analize
make
```

**Su CMake (Unix / Windows)**
```bash
git clone [https://github.com/jusu-vartotojas/studentu-analize.git](https://github.com/jusu-vartotojas/studentu-analize.git)
cd studentu-analize
mkdir build && cd build
cmake ..
cmake --build .
```

## Paleidimo instrukcija

**Unix (Make)**: `./studentai`  
**Unix/Windows (CMake)**: `./build/studentai` (arba `.exe` Windows aplinkoje).

**Svarbu:** Programa automatiškai naudoja `output/` aplanką rezultatams. Jei jo nėra, susikurkite rankiniu būdu.

## Programos naudojimas

Paleidus programą, pateikiamas meniu:
1. Įvesti duomenis ranka.
2. Skaityti iš `kursiokai.txt`.
3. Atsitiktinis pažymių generavimas.
4. Automatinis visų duomenų generavimas.
5. Baigti darbą.
6. Sugeneruoti 5 testinius failus (nuo 1k iki 10M įrašų).
7. Atlikti pilną konteinerių ir strategijų greičio tyrimą.

---

## Konteinerių tyrimas

**Testavimo sistema**
* **OS:** Windows 10/11 | **CPU:** Intel Core i7 / AMD Ryzen 7 | **RAM:** 16 GB | **Saugykla:** SSD NVMe.

**Nuskaitymo laikas (s) — vidurkis**

| Įrašų sk. | vector | list | deque |
|---|---|---|---|
| **1 000** | 0.002 | 0.002 | 0.002 |
| **10 000** | 0.019 | 0.020 | 0.018 |
| **100 000** | 0.180 | 0.182 | 0.174 |
| **1 000 000** | 1.768 | 1.829 | 1.756 |
| **10 000 000**| 18.123 | 18.380 | 17.773 |

---

## Strategijų tyrimas

**Skirstymo laikas (s) — vidurkis**

| Konteineris | Strategija | 100k įrašų | 1M įrašų | 10M įrašų |
|---|---|---|---|---|
| **std::vector** | S1 (2 nauji) | 0.022 | 0.204 | 2.445 |
| | S2 (1 naujas) | 0.018 | 0.183 | 2.196 |
| | S3 (partition)| 0.025 | 0.246 | 2.952 |
| **std::list** | S1 (2 nauji) | 0.027 | 0.267 | 2.581 |
| | S2 (1 naujas) | 0.022 | 0.241 | 2.313 |
| | S3 (partition)| 0.025 | 0.288 | 2.764 |
| **std::deque** | S1 (2 nauji) | 0.018 | 0.178 | 1.782 |
| | S2 (1 naujas) | 0.021 | 0.223 | 2.230 |
| | S3 (partition)| 0.030 | 0.328 | 3.280 |

### Išvados
* **Efektyviausia strategija:** S2 daugeliu atvejų pasirodė efektyvesnė už S1, nes sumažina atminties kopijavimo poreikį. Tačiau S1 su `std::deque` užfiksavo absoliučiai greičiausią skirstymo laiką (1.78s ties 10M).
* **Konteinerių palyginimas:** `std::deque` ir `std::vector` ženkliai lenkia `std::list` tiek nuskaitymo, tiek apdorojimo fazėse dėl geresnio CPU spartinančiosios atminties (cache) panaudojimo.
* **Stable Partition (S3):** Nors ši strategija yra algoritmiškai "švari", šiame specifiniame studentų duomenų kontekste ji nusileido optimizuotam S2 variantui.
