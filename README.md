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

- example1 – mały labirynt dwuwymiarowy z drogą o długości 12
- example2 – mały labirynt jednowymiarowy z drogą o długości 5
- example3 – mały labirynt trójwymiarowy, ale jeden wymiar jest zdegenerowany, pozycja końcowa jest pozycją początkową
- example4 – mały labirynt trójwymiarowy z drogą o długości 4
- example5 – duży labirynt jednowymiarowy bez drogi
- error00 – ewidentnie za duży labirynt
- error10 – rozmiar labiryntu nie może być zerowy
- error26 – pozycja (początkowa) musi być w pustej kostce
- error30 – współrzędne pozycji (końcowej) muszą być dodatnie
- error40 – liczba opisująca położenie ścian ma za dużo bitów
- error50 – dane wejściowe mają za dużo linii

**Studenckie:**

- Folder kwasow:
  - kwasowski_1 - example1 + zera wiodące w linijkach 1-3 i kodzie hex
  - kwasowski_2 - example1 + ale ma spacje wiodące, między liczbami i na końcu linijki
  - kwasowski_3 - example1 + tabulatory brzydkie
  - kwasowski_4 - example4 + brzydkie wejście (tabulatory, spacje, zera)
  - kwasowski_5 - (error) pierwsza linijka wejścia zawiera tekst
  - kwasowski_6 - (error) mała litera i spacja w hexie (mała litera nie jest błędna, spacja owszem)
  - kwasowski_7 - (error) wymiar labiryntu większy niż `SIZE_MAX`
  - kwasowski_8 - (error) trzecia linijka zawiera za mało danych
  - kwasowski_9 - (error) dane z `R` w czwartej linijce są rozdzielone na dwie linijki (czyli jest ich za mało w czwartej linijce)
- Folder etiaro
  - Folder 2D - losowe testy dwuwymiarowe
  - Folder 3D - losowe testy trójwymiarowe
  - Folder 4-8D - losowe testy 4-8-wymiarowe, niektóre dość duże (długi czas wykonywania)
- Folder rentib
  - Folder hex106 - losowe testy z liczbą opisującą labirynt w zapisie szesnastkowym, rozmiar labiryntu nie przekracza znacznie 10^6
  - Folder hex1018 - losowe testy z liczbą opisującą labirynt w zapisie szesnastkowym, rozmiar labiryntu nie przekracza znacznie 10^18
  - Folder rnd106 - losowe (potężne) testy z liczbą opisującą labirynt w formie R ..., jest wiele znaków białych
