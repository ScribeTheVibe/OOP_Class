# Studentų Analizė

Programa skirta studentų duomenų nuskaitymui, rūšiavimui ir skirstymui į dvi grupes: **kietiakus** (galutinis ≥ 5.0) ir **vargšiukus** (galutinis < 5.0).

## Turinys
- [Versijų istorija](#versijų-istorija)
- [Diegimo instrukcija](#diegimo-instrukcija)
- [Paleidimo instrukcija](#paleidimo-instrukcija)
- [Programos naudojimas](#programos-naudojimas)
- [Konteinerių tyrimas](#konteinerių-tyrimas)
- [Strategijų tyrimas](#strategijų-tyrimas)

---

## Versijų istorija

| Versija | Aprašas |
|---------|---------|
| v0.1 | Pradinis variantas: rankinis įvedimas, skaičiavimai |
| v0.2 | Failo nuskaitymas, išvedimas į failą |
| v0.3 | Rūšiavimas, studentų skirstymas į dvi grupes |
| v0.4 | Atsitiktinis generavimas, keli išvedimo formatai |
| v1.0 | `std::vector`, `std::list`, `std::deque` palaikymas; 3 skirstymo strategijos; greičio tyrimas |

---

## Programos naudojimas

Paleidus programą, pateikiamas meniu:

```
Pasirinkite programos eigą:
1 - ranką,
2 - generuoti tik pažymius,
3 - generuoti studentų vardus, pavardės ir pažymius,
4 - skaityti studentus iš failo,
5 - testavimas su failais,
6 - generuoti failą,
7 - baigti darbą: 7
```

---

## Konteinerių tyrimas

> **Testavimo sistema**
> * **CPU:** AMD ryzen 5 5600x 
> * **RAM:** 16 gb
> * **Saugykla:** 1tb ssd
> * **OS:** Windows 11
> * **Kompiliatorius:** g++

Visi laikai — **3 paleidimų vidurkis** (sekundėmis). Failai generuoti vieną kartą prieš tyrimą ir nekeisti tarp bandymų. *(Pateikti duomenys remiasi 1-osios strategijos nuskaitymo ir rūšiavimo matavimais).*

### Nuskaitymo laikas (s)

| Įrašų sk. | vector | list | deque |
|-----------|--------|------|-------|
| 1 000 | 0.003 | 0.002 | 0.002 |
| 10 000 | 0.020 | 0.022 | 0.021 |
| 100 000 | 0.209 | 0.235 | 0.227 |
| 1 000 000 | 2.108 | 2.104 | 2.021 |
| 10 000 000 | 21.379 | 21.387 | 20.923 |

### Rūšiavimo laikas (s)

| Įrašų sk. | vector | list | deque |
|-----------|--------|------|-------|
| 1 000 | 0.001 | 0.000 | 0.001 |
| 10 000 | 0.008 | 0.003 | 0.012 |
| 100 000 | 0.111 | 0.042 | 0.174 |
| 1 000 000 | 1.581 | 0.607 | 2.075 |
| 10 000 000 | 19.549 | 9.345 | 26.450 |

---

## Strategijų tyrimas

Matuojamas tik skirstymo žingsnis (nuskaitymas ir rūšiavimas neįskaičiuoti).

### Skirstymo laikas (s) — 100 000 įrašų

| Strategija | vector | list | deque |
|------------|--------|------|-------|
| S1 — du nauji konteineriai | 0.026 | 0.038 | 0.028 |
| S2 — vienas naujas, trinimas | 0.023 | 0.041 | 0.026 |
| S3 — `std::partition` + `reserve` | 0.015 | 0.038 | 0.022 |

### Skirstymo laikas (s) — 1 000 000 įrašų

| Strategija | vector | list | deque |
|------------|--------|------|-------|
| S1 | 0.301 | 0.380 | 0.253 |
| S2 | 0.262 | 0.376 | 0.268 |
| S3 | 0.130 | 0.380 | 0.201 |

### Skirstymo laikas (s) — 10 000 000 įrašų

| Strategija | vector | list | deque |
|------------|--------|------|-------|
| S1 | 3.325 | 4.149 | 2.627 |
| S2 | 2.892 | 4.119 | 3.171 |
| S3 | 1.239 | 4.161 | 2.172 |

### Strategijų aprašas

**S1 — du nauji konteineriai**
Bendras `visi` konteineris lieka nepakeistas; sukuriami du nauji: `gerai` ir `blogai`. Kiekvienas studentas egzistuoja dviejuose konteineriuose vienu metu — tai dvigubai daugiau atminties. Paprasta realizacija, bet atminties atžvilgiu neefektyviausia.

**S2 — vienas naujas konteineris + trinimas iš originalo**
Sukuriamas tik `blogai` konteineris; vargšiukai iškeliami į jį ir **ištrinami** iš `visi`. Po operacijos `visi` lieka tik kietiakai. `std::vector` ir `std::deque` naudoja `std::remove_if` + `erase` idiomą; `std::list` — savo `remove_if` metodą (O(n), be poslinkių). Atminties efektyviau, tačiau `vector`/`deque` trinimas gali sukelti elementų poslinkius.

**S3 — `std::partition` + `reserve`**
Paremta S2, papildyta dviem optimizacijomis:
1. `blogai.reserve(visi.size())` vektoriui — iš anksto rezervuoja atmintį, pašalina dinaminius perskirstymus `push_back` metu.
2. `std::partition` vietoje `std::remove_if` — vienas O(n) praėjimas su `swap` operacijomis, be papildomo buferio ir be elementų tvarkos išsaugojimo kaštų (`std::stable_partition` yra O(n log n) arba O(n) su O(n) papildomu buferiu). Elementai perkeliami į `blogai` per `std::make_move_iterator`, išvengiant kopijavimo.
`std::list` naudoja tą patį `remove_if` kelią kaip S2 — sąrašui `partition` nenaudinga, nes atsitiktinė prieiga nepalaikoma.

### Išvados

Remiantis atlikto tyrimo rezultatais, galime padaryti šias išvadas:

* **Nuskaitymas iš failo yra I/O nulemtas procesas:** Visi trys konteineriai rodo labai panašų nuskaitymo greitį (~21 sek. ties 10M įrašų). Tai rodo, kad didžiausias stabdis čia yra darbas su kietuoju disku ir teksto srautų (`fstream`) apdorojimas, o ne duomenų įterpimas į pačius konteinerius.
* **`std::list` karaliauja rūšiavime:** Priešingai lūkesčiams apie lėtesnį `list` veikimą, jo `sort()` metodas veikia daugiau nei dvigubai greičiau už `std::vector` ir `std::deque` (9.3 s vs 19.5 s ties 10M). Taip yra todėl, kad rikiuojant elementus sąraše keičiamos tik rodyklės (pointers), o ne kopijuojami patys objektų duomenys atmintyje.
* **3-ioji strategija (`std::partition`) su `std::vector` yra absoliuti skirstymo lyderė:** Atliekant skirstymą 10M įrašų mastu, `vector` atveju S3 užtruko vos 1.239 s, kai pirmoji strategija užėmė 3.325 s. Tai įrodo, kad algoritmų lygio optimizacija (`std::partition`) bei išankstinis atminties rezervavimas (`reserve`) drastiškai sumažina nereikalingo duomenų kopijavimo kaštus.
* **Sąrašui (`std::list`) strategijos neturi įtakos skirstymui:** Skirstymo laikai visose trijose strategijose ties 10M įrašų buvo beveik identiški (~4.1 s). Kadangi sąrašas nepalaiko atsitiktinės prieigos (random access), jis negali pilnai išnaudoti `std::partition` algoritmo privalumų, o elementų trynimas / iškėlimas iš jo prigimties ir taip reikalauja vienodo rodyklių perjungimo.
