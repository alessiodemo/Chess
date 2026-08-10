import { useState } from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from './assets/vite.svg'
import heroImg from './assets/hero.png'
import './App.css'
import { use } from 'react'
import { useLayoutEffect } from 'react'
import Panel from '../components/panel/panel.jsx'
import Scacchiera from '../components/chesstable/chesstable.jsx'

function App() {
  const [ board, setBoard ] = useState(null)
  const [ gameId, setGameId ] = useState(null);
  const [ mode, setMode ] = useState(null);
  const [ count, setCount ] = useState(0);
  const [ state, setState ] = useState(null);

  return state ? (
    <>
      <Scacchiera posizione={state.position} onMossa={muovi} />
      <Panel state={state}/>
    </>
  ) : (
    <div id="setup">
      <button onClick={ () => newMatch('pc', 'Bianco') }>Gioca come Bianco (vs Computer)</button>
      <button>Gioca come Nero (vs Computer)</button>
      <button>Computer vs Computer</button>
    </div>
  );

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
