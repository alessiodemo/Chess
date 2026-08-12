
export default function Panel({ state }) {
    return (
      <div className="panel">
        <div className={`turn-badge ${state.turn === 'Bianco' ? 'is-white' : 'is-black'}`}>
          {state.over ? state.status : `Turno: ${state.turn}`}
        </div>
        <h2 className="panel-title">Mosse</h2>
        <ol className="history">
          {state.history.map((mossa, i) => <li key={i}>{mossa}</li>)}
        </ol>
      </div>
    );
  }
