# ♟️ Ajedrez en C (Raylib)

**Motor de ajedrez completo** desarrollado en C puro con **Raylib** para la interfaz gráfica.  
Single-file, zero dependencies (except Raylib), ~900 líneas de C puro.

---

## 📁 Archivo principal
* **`prbchs1.c`** — Lógica completa: tablero, validaciones, turnos, render, IA (próximamente), todo.

---

## ✅ Estado del proyecto: **v1.0 — COMPLETO**

- [x] Movimientos básicos y validaciones de todas las piezas
- [x] Enroque corto y largo (con validaciones completas)
- [x] Captura al paso (*en passant*)
- [x] Promoción de peón con **menú visual interactivo** (Q/R/B/N)
- [x] Detección de jaque + highlight visual
- [x] **Detección de piezas clavadas** (pinning) vía simulación
- [x] **Detección de jaque mate y tablas** (ahogado / rey ahogado)
- [x] Pantalla de fin de partida con overlay + mensaje + **botón R para reiniciar**
- [x] En passant tracking (`paso_f/paso_c`)
- [x] Interfaz gráfica completa: selección, highlight, movimientos legales, jaque en rojo
- [x] **Componente computarizado (IA): Muy pronto™** 🤖✨
- [x] Protocolo UCI: *En la cola de features* 📋

---

## 🎮 Controles
- **Click izquierdo**: Seleccionar/mover pieza
- **R**: Reiniciar partida (en cualquier momento, incluso tras mate/tablas)
- **ESC / Cerrar ventana**: Salir

---

## 🛠️ Build & Run (Windows)

```bash
# Requisitos: gcc + Raylib instalado
gcc prbchs1.c -o chess -lraylib -lopengl32 -lgdi32 -lwinmm -lm
./chess
```

> **Tip:** Usa `run.bat` si lo tienes configurado.

---

## 🏗️ Arquitectura (resumen mental)

```
prbchs1.c
├── main()                    // Game loop, input, estado_juego, render
├── Piezas & Tablero          // struct pieza[8][8], move counter, en passant
├── Validaciones              // vltr_peon, torre, caballo, alfil, reina, rey
├── Reglas especiales         // Enroque, en passant, promoción, pinning
├── Jaque & Mate              // esta_en_jaque, casilla_atacada, tiene_movimientos_legales
├── UI/Render                 // Raylib: texturas, menú promoción, overlays mate/tablas
└── Utilidades                // memcpy, sqrtf, round, etc.
```

---

## 🤖 Próximos pasos (Roadmap)

| Feature | Estado | Notas |
|---------|--------|-------|
| **Minimax + Alpha-Beta** | 🔜 *Muy pronto™* | Profundidad 3-4, evaluación material + PST |
| **Bitboards** | 📋 *En cola* | `uint64_t` por tipo de pieza, magic bitboards |
| **UCI Protocol** | 📋 *En cola* | Para jugar vs Stockfish / torneos |
| **Tabla de hash (TT)** | 📋 *Sueño* | Transposition table + iterative deepening |
| **C++ Port** | 🛠️ *En progreso* | Bitboards + UCI + motor moderno |

---

## 📜 Licencia
**MIT** — Úsalo, rómpelo, mejóralo, aprende con él.

---

## 💭 Nota personal

> *"Empecé esto sin saber bien qué era un puntero. Hoy tengo un motor que juega legal, detecta mate, tiene UI y hasta menú de promoción.  
> Lo siguiente: C++ + bitboards + carritos con física + simulación de agujero negro.  
> Si tú también estás aprendiendo: **escribe código, rómpelo, diviértete**."*  
> — **Yisus** 💛

---

**⭐ Si te gusta, dale una estrella al repo.  
🐛 ¿Bug? Abre un issue.  
💡 ¿Idea? PR bienvenido.**