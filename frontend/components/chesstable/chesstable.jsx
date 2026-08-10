import { Chessboard } from 'react-chessboard';

export default function Scacchiera({ posizione, onMossa }) {
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