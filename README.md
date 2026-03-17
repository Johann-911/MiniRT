# MiniRT

Kleines Raytracing-Projekt (42-style) — rendert einfache Szenen aus `.rt`-Dateien.

## Inhalt
- Quellcode: `main/`
- Header: `inc/`
- Abhängigkeiten: `minilibx-linux/`, `Printf/`, `Printf/Libft`

## Voraussetzungen
- POSIX/Linux
- `cc` (clang oder gcc), `make`
- X11-Entwicklerbibliotheken (für MiniLibX)

## Build
Im Projekt-Root ausführen:

```bash
make
```

Das erstellt die ausführbare `MiniRT`.

Wenn `minilibx-linux` oder die Hilfsbibliotheken nicht gebaut sind, werden sie automatisch durch das Makefile gebaut.

## Ausführung

```bash
./MiniRT scenes/example.rt
```

Passe den Dateinamen an deine .rt-Szene an.

## Häufige Probleme
- Linker-Fehler wegen doppelter Symbole: stelle sicher, dass nur eine Implementierung von Hilfsfunktionen (z. B. `vec3_*`) vorhanden ist oder markiere sie `static`.
- Änderungen lokal gesichert halten: vor einem `git pull` entweder committen, stashen oder auf einem WIP-Branch speichern.

## Nützliche Git-Kommandos

- Backup deines Standes:

```bash
git branch backup-main
git push -u origin backup-main
```

- Stashen vor Pull:

```bash
git stash push -m "wip"
git pull
git stash pop
```

## Struktur (Auszug)

- `main/` – Quellcode
- `inc/` – Header
- `minilibx-linux/` – MiniLibX
- `Printf/` – printf implementation + libft

## Weiteres
Wenn du möchtest, schreibe ich noch eine kurze `CONTRIBUTING.md` oder passe das `Makefile` weiter an.

---
Autor: Projekt-Workspace
