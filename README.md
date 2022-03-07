# IPP_testy

Repozytorium do dzielenia się testami z IPP

## Instrukcja dodawania testów

1. Sklonuj repozytorium na swoje konto na Githubie.
2. Dodaj testy i oczekiwane wyjście do testów w katalogu `testy_labirynt`.
3. Otwórz pull requesta w tym repozytorium (postaram się jak najszybciej zatwierdzić).

## Instrukcja nazywania testów

Aby uniknąć powtarzających się nazw testów nazwij swoje testy pierwszą literą imienia oraz nazwiskiem.

Reprezentatywny przykład. Jan Kowalski chciał dodać swoje testy na nowy, nieznany do tej pory edge case.
Sklonował repozytorium i dodał do niego pliki `jkowalski.in`, `jkowalski.out` oraz `jkowalski.err`.
Znalazł też inne fajne testy, więc dodał jeszcze `jkowalski_1.in`, `jkowalski_1.out` i `jkowalski_1.err`.
Bądź jak Jan Kowalski.

Ważne, żeby pliki dotyczące tych samych testów miały te same nazwy. Plik `*.in` zawiera wejście, `*.out` wyjście
standardowe,  a `*.err` wyjście stderr.
