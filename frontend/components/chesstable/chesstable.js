import { Chessboard } from 'react-chessboard';

function Scacchiera({ posizione, onMossa }) {
    return (
        <Chessboard 
            position={posizione}
            onPieceDrop={(source, target) => {
                onMossa(source, target);
                return true;
            }}
        />
    );
}