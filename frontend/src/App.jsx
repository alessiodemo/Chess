import { useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from './assets/vite.svg'
import heroImg from './assets/hero.png'
import './App.css'
import { use } from 'react'
import { useLayoutEffect } from 'react'
import Panel from '../components/panel/panel.jsx'
import Scacchiera from '../components/chesstable/chesstable.jsx'
import DeleteButton from '../components/exit_button/index.jsx'

function App() {
  const [ board, setBoard ] = useState(null)
  const [ gameId, setGameId ] = useState(null);
  const [ mode, setMode ] = useState(null);
  const [ count, setCount ] = useState(0);
  const [ state, setState ] = useState(null);
  const [ page, setPage ] = useState("home");

  return state ? (
    <div className="game">
      <header className="game-bar">
        <h1 className="brand">♟ Scacchiera</h1>
        <DeleteButton onDelete={exit}/>
      </header>
      <div className="table">
        <Scacchiera posizione={state.position} onMossa={muovi} />
        <Panel state={state}/>
      </div>
    </div>
  ) : page === 'computer' ? (
    <div id="setup">
      <button onClick={() => setPage('home')}>
        Back to Home
      </button>

      <h1>Play vs PC</h1>
      <p className="subtitle">Choose your Color</p>

      <button onClick={ () => newMatch('pc', 'Bianco') }>Play as White (vs Computer)</button>
      <button onClick={ () => newMatch('pc', 'Nero') }>Play as Black (vs Computer)</button>

    </div>
  ) : (
    <div id="setup">
      <h1>♟ Scacchiera</h1>
      <p className="subtitle">Scegli come vuoi giocare</p>
      <button onClick={ () => setPage("computer") }>Plays against Computer</button>
      <button onClick={ () => newMatch('cc') }>Computer vs Computer</button>
    </div>
  )

  async function newMatch(nuovaMode, colore) {
    const params = new URLSearchParams({ mode: nuovaMode });
    if (colore) params.set('color', colore);

    const res = await fetch(`/api/games?${params}`, { method: 'POST' });
    const state = await res.json();
    setGameId(state.id);
    setMode(nuovaMode);
    setState(state);
  }

  async function muovi(source, target) {
    // TODO: come newMatch, ma verso /api/games/${gameId}/move?from=...&to=...
    // ricordati setState(...) alla fine, altrimenti la mossa non compare
    const params = new URLSearchParams({ from: source, to: target });
    const res = await fetch(`/api/games/${gameId}/move?${params}`, { method: 'POST' });

    if(!res.ok)
        return

    const state = await res.json();
    setState(state);


  }

  async function exit() {
    const res = await fetch(`/api/games/${gameId}`, { method: 'DELETE' });
    setState(null);
    setGameId (null);
    setMode(null);
  }

  useLayoutEffect( () => {
    if (mode != 'cc' || !state || state.over) return;

    const timer = setTimeout( async () => {
      const res = await fetch(`/api/games/${gameId}/step`, { method: 'POST' });
      const state = await res.json();
      setState(state);
    }, 400);

    return () => clearTimeout(timer);
  }, [state, mode]);
}

export default App;
