# IPP_testy

Repozytorium do dzielenia się testami z IPP.

## Dodawanie testów

1. Zrób forka repozytorium na swoje konto na Githubie.
2. Dodaj testy i oczekiwane wyjście do  katalogu `testy_labirynt`, bądź podkatalogu, jeśli jest ich dużo.
3. [Otwórz pull requesta](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request-from-a-fork) w tym repozytorium (postaram się jak najszybciej zatwierdzić).

## Nazywanie testów

Aby uniknąć powtarzających się nazw testów nazwij swoje testy pierwszą literą imienia oraz nazwiskiem.

Reprezentatywny przykład. Jan Kowalski chciał dodać swoje testy na nowy, nieznany do tej pory edge case.
Sklonował repozytorium i dodał do niego pliki `jkowalski.in`, `jkowalski.out` oraz `jkowalski.err`.
Znalazł też inne fajne testy, więc dodał jeszcze `jkowalski_1.in`, `jkowalski_1.out` i `jkowalski_1.err`.
Bądź jak Jan Kowalski.

Ważne, żeby pliki dotyczące tych samych testów miały te same nazwy. Plik `*.in` zawiera wejście, `*.out` wyjście
standardowe,  a `*.err` wyjście stderr.

## Opisy testów (labirynt)

**Oficjalne:**
<details><summary>Pokaż opisy</summary>
  <ul>
    <li> example1 – mały labirynt dwuwymiarowy z drogą o długości 12 </li>
    <li> example2 – mały labirynt jednowymiarowy z drogą o długości 5 </li>
    <li> example3 – mały labirynt trójwymiarowy, ale jeden wymiar jest zdegenerowany, pozycja końcowa jest pozycją początkową </li>
    <li> example4 – mały labirynt trójwymiarowy z drogą o długości 4 </li>
    <li> example5 – duży labirynt jednowymiarowy bez drogi </li>
    <li> error00 – ewidentnie za duży labirynt </li>
    <li> error10 – rozmiar labiryntu nie może być zerowy </li>
    <li> error26 – pozycja (początkowa) musi być w pustej kostce </li>
    <li> error30 – współrzędne pozycji (końcowej) muszą być dodatnie </li>
    <li> error40 – liczba opisująca położenie ścian ma za dużo bitów </li>
    <li> error50 – dane wejściowe mają za dużo linii </li>
  </ul>
</details>

**Studenckie:**

**Uwaga!** *Niektóre z tych testów zwracją inne kody blędów niż testy oficjalne. W szczególności, gdy testy zwracają
`ERROR 0` dla zbyt dużego labiryntu te testy mogą uważać `ERROR 1` za poprawne wyjście (ponieważ iloczyn wymiarów jest
większy niż `SIZE_MAX`). Podobnie gdy testy oficjalne zwracają `ERROR 2/3`, ponieważ początek/koniec są w niepustej kostce, niektóre
z tych testów mogą zwracać `ERROR 4` (niepoprawna liczba w czwartej linijce). Nie należy się tym przejmować.*

<details><summary>Folder kwasow</summary>
  <ul>
    <li> kwasowski_1 - example1 + zera wiodące w linijkach 1-3 i kodzie hex </li>
    <li> kwasowski_2 - example1 + ale ma spacje wiodące, między liczbami i na końcu linijki </li>
    <li> kwasowski_3 - example1 + tabulatory brzydkie </li>
    <li> kwasowski_4 - example4 + brzydkie wejście (tabulatory, spacje, zera) </li>
    <li> kwasowski_5 - (error) pierwsza linijka wejścia zawiera tekst </li>
    <li> kwasowski_6 - (error) mała litera i spacja w hexie (mała litera nie jest błędna, spacja owszem) </li>
    <li> kwasowski_7 - (error) wymiar labiryntu większy niż `SIZE_MAX` </li>
    <li> kwasowski_8 - (error) trzecia linijka zawiera za mało danych </li>
    <li> kwasowski_9 - (error) dane z `R` w czwartej linijce są rozdzielone na dwie linijki (czyli jest ich za mało w czwartej linijce) </li>
    <li> kwasowski_10 - (error) spacje między `0x`, a hexem </li>
    <li> kwasowski_11 - (error) niby wszystkie linijki są, ale jest dodatkowa linijka przerwy między pierwszą i drugą </li>
  </ul>
</details>

<details><summary>Folder etiaro</summary>
  <ul>
    <li> Folder 2D - losowe testy dwuwymiarowe
    <li> Folder 3D - losowe testy trójwymiarowe
    <li> Folder 4-8D - losowe testy 4-8-wymiarowe, niektóre dość duże (długi czas wykonywania)
  </ul>
</details>

<details><summary>Folder rentlib</summary>
  <ul>
    <li> Folder hex106 - losowe testy z liczbą opisującą labirynt w zapisie szesnastkowym, rozmiar labiryntu nie przekracza znacznie 10^6
    <li> Folder hex1018 - losowe testy z liczbą opisującą labirynt w zapisie szesnastkowym, rozmiar labiryntu nie przekracza znacznie 10^18
    <li> Folder rnd106 - losowe (potężne) testy z liczbą opisującą labirynt w formie R ..., jest wiele znaków białych, rozmiar labiryntu nie przekracza znacznie 10^6
    <li> Folder rnd109 - losowe (potężne) testy z liczbą opisującą labirynt w formie R ..., rozmiar labiryntu nie przekracza znacznie 10^9, aby uniknąć ERROR 0 jest wiele niedużych wymiarów
  </ul>
</details>

<details><summary>Folder wojtekr</summary>
  <ul>
    <li> zly01 - 3. linijka położenie większe niż wymiar
    <li> zly02 - 2. linijka położenie większe niż wymiar
    <li> zly03 - 2. linijka liczba za dużo
    <li> zly04 - 3. linijka pusta
    <li> zly05 - 2. linijka pusta
    <li> zly06 - 4. linijka niepoprawna
    <li> zly07 - 4. linijka liczba za dużo
    <li> zly08 - 4. linijka liczba za mało
    <li> zly09 - 4. linijka pusta
    <li> zly10 - 2. linijka zawiera 0
    <li> zly11 - 3. linijka zawiera 0
    <li> zly12 - 5. linijka istnieje w 0x
    <li> zly13 - 5. linijka istnieje w R
    <li> zly14 - 4. linijka dodatkowy znak
    <li> zly15 - 2. linijka pozycja w kostce
    <li> zly16 - 4. linijka zawiera znak nie hexowy
    <li> zly17 - 3. linijka pozycja w kostce
    <li> zly18 - 4. linijka liczba R ponad UINT32_MAX
    <li> zly19 - 4. linijka m jest zerem
    <li> zly20 - 4. linijka spacja po x
    <li> zly21 - 4. linijka spacja po 0
    <li> test12 - 4. linijka liczymy liczby do r włącznie
    <li> test13 - 4. linijka liczby mogą być zerami
  </ul>
</details>

<details><summary>Folder fuchczyk</summary>
  <ul>
    <li> pfuchs1 - Brak 2. linijki (EOF w pierwszej) </li>
    <li> pfuchs2 - Niepoprawna 2. linijka (tylko EOF) </li>
    <li> pfuchs3 - Niepoprawna 1. linijka (pusta - tylko EOF) </li>
    <li> pfuchs4 - Brak 1. linijki (tylko EOF) </li>
    <li> pfuchs5 - Niepoprawna 3. linijka (pusta - tylko EOF) </li>
    <li> pfuchs6 - Brak 3. linijki (EOF w drugiej) </li>
    <li> pfuchs7 - Brak 4. linijki (EOF w trzeciej) </li>
    <li> pfuchs8 - Niepoprawna 4. linijka (pusta - tylko EOF) </li>
    <li> pfuchs9 - Pomieszanie formatów: rozpoczęcie od "0R"
  </ul>
</details>

<details><summary>Folder az</summary>
  <ul>
    <li> Folder tsh_h_50mln -  Kilka testów 3D o wymiarach 10000 x 10000 x 4 o tak dobranej trasie od startu do końca aby jej przebycie wymagało przejścia około 50 milionów kostek
    <li> Folder a - 64 testy o liczbie wymiarów 1,2, ... ,64. Rozmiar każdego wymiaru jest równy 2. W każdym są tylko puste kostki. Start i koniec tak dobrane aby długość trasy była równa liczbie wymiarów.
    <li> Folder b - 64 testy o liczbie wymiarów 1,2, ... ,64. Rozmiar każdego wymiaru jest równy 2. W każdym są tylko puste kostki. Start i koniec w tej samej kostce.
  </ul>
</details>
  
<details><summary>Folder correctErrorHandling</summary>
  <ul>
    <li> Proste testy sprawdzające poprawność wejśćia.
    <li> UWAGA !!! EOF na końcu linij traktujemy jako błąd tej linii. Oraz jeśli jest ściana na pozycji strtowej, zwracamy ERROR 2, analogicznie dla pozycji końcowej. (Jeśli ktoś zwraca to jako błąd w kolejnej linijce, to powinien mieć poprawne wszystkie testy oprócz stu).
  </ul>
</details>

## Czasy wykonywania

Czasy zmierzone na serwerze `students` przy użyciu komendy `time` (czasy dotyczą czasów `real`) **bez valgrinda**.

| Nazwa testu      | Czas      |
| ---------------- | --------- |
| *Oficjalne*      | 0m1.091   |
| *kwasow*         | 0m0.250   |
| *etiaro/1D*      | 0m10.388  |
| *etiaro/2D*      | 0m10.982  |
| *etiaro/3D*      | 0m6.838   |
| *etiaro/4-8D*    | 2m11.267  |
| *rentib/hex106*  | 0m41.980  |
| *rentib/hex1018* | 3m28.198  |
| *rentib/rnd106*  | 16m3.333  |
| *rentib/hex109*  | 109m4.448 |
| *wojtekr*        | 0m17.562  |
| *tsh_h_50mln*    | 0m56.014  |
| *fuchczyk*       | 0m0.170   |
