import './style.css';

export default function DeleteButton({onDelete}) {
    return (
    <button className="exit-button" onClick={ onDelete }>
        ✕ Termina partita
    </button>
    );
}

