TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    magic-bits/src/slider_attacks.cpp \
    move.cpp \
    board.cpp \
    king_attacks.cpp \
    evaluation_function.cpp \
    game.cpp \
    minimax.cpp

HEADERS += \
    magic-bits/src/common.h \
    magic-bits/src/slider_attacks.h \
    move.h \
    board.h \
    move_generator.h \
    bit.h \
    king_attacks.h \
    pawn_moves.h \
    knight_attacks.h \
    evaluation_function.h \
    game.h \
    minimax.h

DISTFILES += \
    magic-bits/magics/bishop_attack_table.magic \
    magic-bits/magics/bishop_magics.magic \
    magic-bits/magics/bishop_masks.magic \
    magic-bits/magics/bishop_offsets.magic \
    magic-bits/magics/bishop_shifts.magic \
    magic-bits/magics/rook_attack_table.magic \
    magic-bits/magics/rook_magics.magic \
    magic-bits/magics/rook_masks.magic \
    magic-bits/magics/rook_offsets.magic \
    magic-bits/magics/rook_shifts.magic
