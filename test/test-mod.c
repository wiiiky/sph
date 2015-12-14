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

int main (int argc, char *argv[]) {
    JacModule *mod=jac_module_load("./test-mod.so");
    if(!mod) {
        return 1;
    }
    if(mod->m_init()!=0) {
        return 2;
    }
    if(mod->m_accept(NULL)!=1) {
        return 3;
    }
    if(mod->m_recv(NULL, NULL, 0)!=2) {
        return 4;
    }
    return 0;
}
