TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    magic-bits/src/magic_bits.cpp \
    magic-bits/src/slider_attacks.cpp \
    magic-bits/src/slider_attacks_test.cpp \
    main.cpp \
    main.cpp

HEADERS += \
    magic-bits/src/common.h \
    magic-bits/src/slider_attacks.h

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
