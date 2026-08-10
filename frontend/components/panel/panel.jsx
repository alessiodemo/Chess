
export default function Panel({ state }) {
    return (
      <div>
        <p>{state.turn}</p>
        <ol>
          {state.history.map((mossa, i) => <li key={i}>{mossa}</li>)}
        </ol>
      </div>
    );
  }
