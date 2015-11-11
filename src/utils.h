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
#ifndef __SPH_UTILS_H__
#define __SPH_UTILS_H__


#if defined(__GNUC__) && (__GNUC__ > 2) && defined(__OPTIMIZE__)
#define LIKELY(expr)    __builtin_expect(!!(expr), 1)
#define UNLIKELY(expr)  __builtin_expect(!!(expr), 0)
#else
#define LIKELY(expr) (expr)
#define UNLIKELY(expr) (expr)
#endif



#endif
