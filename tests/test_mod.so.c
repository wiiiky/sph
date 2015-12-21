/*
 * Copyright (C) 2015 Wiky L
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.";
 */
#include <sph.h>
#include <stdlib.h>

static int m_accept(SphSocket *socket) {
    return 1;
}

static int m_recv(SphSocket *socket, const uint8_t *pdata, unsigned int len) {
    return 2;
}

JacModule testMod = {
    NULL,
    m_accept,
    m_recv
};

JacModule *JacInit_test_mod(void) {
    return &testMod;
}
