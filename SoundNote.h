/*
 * This Arduino library implement a system to manage notes for a musical instrument
 * Copyright (C) 2016  Pierre-Loup Martin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SOUNDNOTE_H
#define SOUNDNOTE_H

class SoundNote{
public:

	SoundNote();

	void play();
	void stop();

	void setPitch(unsigned char pitch);
	void setVelocity(unsigned char velocity);

	void setWave(unsigned char wave);
	void setEnv(unsigned char enveloppe);


protected:

	unsigned char _pitch;
	unsigned char _velocity;

	unsigned char _wave;
	unsigned char _env;

	unsigned char _channel;

	bool _isPlaying;


};

class SoundNotes{
public:

	SoundNotes();

	void addNote(SoundNote const& note);
	void removeNote(SoundNote const& note);

protected:

};

#endif