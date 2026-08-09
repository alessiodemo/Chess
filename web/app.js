let board = null;
let gameId = null;
let mode = null;

function testoStato(stato) {
    if (stato.over) return stato.status || 'Partita finita';
    return stato.turn === 'Bianco' ? 'Turno del Bianco' : 'Turno del Nero';
}

function aggiornaStato(stato) {
    const ol = document.getElementById('storico');
    ol.innerHTML = '';
    stato.history.forEach( m => {
        const li = document.createElement('li');
        li.textContent = m;
        ol.appendChild(li);
    });
}

function aggiornaVista(stato) {
    board.position(stato.position);
    document.getElementById('stato').textContent = testoStato(stato);
    aggiornaStato(stato);

    if(!stato.over && mode === 'cc') {
        setTimeout(passoComputerComputer, 400);
    }
}

async function passoComputerComputer() {
  const res = await fetch(`/api/games/${gameId}/step`, { method: 'POST' });
  const stato = await res.json();
  aggiornaVista(stato);
}

function onDragStart() {
    return mode === 'pc';
}

async function onDrop(source, target) {
    const res = await fetch(`/api/games/${gameId}/move?from=${source}&to=${target}`, {method: 'POST'});
    if (!res.ok) {
        return 'snapback';
    }
    const stato = await res.json();
    aggiornaVista(stato);
}

async function nuovaPartita(nuovaMode, colore) {
    mode = nuovaMode;
    const params = new URLSearchParams({ mode: nuovaMode});
    if (colore) params.set('color', colore);

    const res = await fetch(`/api/games?${params.toString()}`, { method: 'POST'});
    const stato = await res.json();
    gameId = stato.id;

    document.getElementById('setup').style.display = 'none';
    document.getElementById('gioco').style.display = 'flex';

    if (!board) {
        board = Chessboard('board' , {
            draggable: true,
            position: stato.position,
            pieceTheme: 'https://cdn.jsdelivr.net/gh/oakmac/chessboardjs@master/website/img/chesspieces/wikipedia/{piece}.png',
            onDragStart,
            onDrop,
        });
    }
    aggiornaVista(stato);
}

document.getElementById('btnPcBianco').addEventListener('click', () => nuovaPartita('pc', 'Bianco'));
document.getElementById('btnPcNero').addEventListener('click', () => nuovaPartita('pc', 'Nero'));
document.getElementById('btnCc').addEventListener('click', () => nuovaPartita('cc'));
document.getElementById('btnNuova').addEventListener('click', () => location.reload());




