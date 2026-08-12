import { Chessboard } from 'react-chessboard';

export default function Scacchiera({ posizione, onMossa }) {

    function conversion(pos) {
        return Object.fromEntries(
            Object.entries(pos).map(
            ([key, value]) => [key, { pieceType: value }]
            )
        )
    }

    return (
        <div className="board-wrap">
        <Chessboard
            options={{
                position: conversion(posizione),
                onPieceDrop: ({ sourceSquare, targetSquare }) => {
                    onMossa(sourceSquare, targetSquare);
                    return true;
                },
            }}
        />
        </div>
    );
}