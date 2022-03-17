# IPP_testy

Repozytorium do dzielenia się testami z IPP

## Instrukcja dodawania testów

1. Zrób forka repozytorium na swoje konto na Githubie.
2. Dodaj testy i oczekiwane wyjście do testów w katalogu `testy_labirynt`.
3. [Otwórz pull requesta](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request-from-a-fork) w tym repozytorium (postaram się jak najszybciej zatwierdzić).

## Instrukcja nazywania testów

Aby uniknąć powtarzających się nazw testów nazwij swoje testy pierwszą literą imienia oraz nazwiskiem.

Reprezentatywny przykład. Jan Kowalski chciał dodać swoje testy na nowy, nieznany do tej pory edge case.
Sklonował repozytorium i dodał do niego pliki `jkowalski.in`, `jkowalski.out` oraz `jkowalski.err`.
Znalazł też inne fajne testy, więc dodał jeszcze `jkowalski_1.in`, `jkowalski_1.out` i `jkowalski_1.err`.
Bądź jak Jan Kowalski.

Ważne, żeby pliki dotyczące tych samych testów miały te same nazwy. Plik `*.in` zawiera wejście, `*.out` wyjście
standardowe,  a `*.err` wyjście stderr.

## Opisy testów

**Oficjalne:**

- example1 – mały labirynt dwuwymiarowy z drogą o długości 12,

- example2 – mały labirynt jednowymiarowy z drogą o długości 5,
- example3 – mały labirynt trójwymiarowy, ale jeden wymiar jest zdegenerowany, pozycja końcowa jest pozycją początkową,
- example4 – mały labirynt trójwymiarowy z drogą o długości 4,
- example5 – duży labirynt jednowymiarowy bez drogi,
- error00 – ewidentnie za duży labirynt,
- error10 – rozmiar labiryntu nie może być zerowy,
- error26 – pozycja (początkowa) musi być w pustej kostce,
- error30 – współrzędne pozycji (końcowej) muszą być dodatnie,
- error40 – liczba opisująca położenie ścian ma za dużo bitów,
- error50 – dane wejściowe mają za dużo linii.

**Studenckie:**

- kwasowski_1 - example1 + zera wiodące w linijkach 1-3 i kodzie hex
- kwasowski_2 - example1 + ale ma spacje wiodące, między liczbami i na końcu linijki
- kwasowski_3 - example1 + tabulatory brzydkie
- kwasowski_4 - example4 + brzydkie wejście (tabulatory, spacje, zera)
- kwasowski_5 - (error) pierwsza linijka wejścia zawiera tekst
- kwasowski_6 - (error) mała litera w hexie i spacja w hexie

- Folder etiaro
  - Folder 2D - losowe testy dwuwymiarowe
  - Folder 3D - losowe testy trójwymiarowe
  - Folder 4-8D - losowe testy 4-8-wymiarowe, niektóre dość duże(długi czas wykonywania)
