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

 /* Warning: this class uses dynamic memory allocation.
  * Compiler won't warn you about using too much memory size.
  * It's up to you to know that you don't overflow what can be used.
  * Each note set occupies 6 bytes of memory, and SoundNotes is 2 bytes per note, + 2.
  * When adding or removing a note, you should have enough contiguous memory to store a temp allocation of the table.
  */

#include "SoundNote.h"

SoundNote::SoundNote(){
	_pitch = 60;
	_velocity = 100;
	_wave = 0;
	_env = 0;

	_stepPlay = 0;

}

void SoundNote::play(){

}

void SoundNote::stop(){

}

void SoundNote::setPitch(unsigned char pitch){
	_pitch = pitch;
}

void SoundNote::setVelocity(unsigned char velocity){
	_velocity = velocity;
}

void SoundNote::setWave(unsigned char wave){
	_wave = wave;
}

void SoundNote::setEnv(unsigned char enveloppe){
	_env = enveloppe;
}

unsigned char SoundNote::getPitch(){
	return _pitch;
}

unsigned char SoundNote::getVelocity(){
	return _velocity;
}

unsigned char SoundNote::getWave(){
	return _wave;
}

unsigned char SoundNote::getEnv(){
	return _env;
}

void SoundNote::setStep(byte step){
	setBit(_stepPlay, step);
}

void SoundNote::clearStep(byte step){
	clearBit(_stepPlay, step);
}

void SoundNote::toggleStep(byte step){
	toggleBit(_stepPlay, step);
}

bool SoundNote::getStep(byte step){
	return _stepPlay & (1 << step);
}




SoundNotes::SoundNotes(){
	notes = NULL;
	notesSize = 0;

}

SoundNotes::~SoundNotes(){
	free(notes);
}

SoundNote* SoundNotes::getNote(int i){
	return notes[i];
}

byte SoundNotes::getNotes(){
	return notesSize;
}

void SoundNotes::addNote(SoundNote* note){
	notesSize++;
	SoundNote **tmp = (SoundNote**)realloc(notes, sizeof(SoundNote) * notesSize);
	if(tmp == NULL){
		return;
	}
	notes = tmp;
	notes[notesSize - 1] = note;
}

void SoundNotes::removeNote(SoundNote* note){
	//decrement count of notes
	notesSize--;

	//If it's 0, then delete notes, as it's empty
	if(notesSize == 0){
		delete(notes);
		return;
	}

	//Realloc the memory for the new table, verify it's ok.
	SoundNote **tmp = (SoundNote**)realloc(notes, sizeof(SoundNote) * notesSize);
	if(tmp == NULL){
		return;
	}

	//Look for the note we want to suppress.
	int top = notesSize + 1;
	int count = 0;

	for(int i = 0; i < top; i++){
		//When found, skip copy.
		if(notes[i] == note){continue;}
		//Copy every other note from table to new memory location.
		tmp[count] = notes[i];
		count++;
	}
	//Then copy the temp table into it's new location. (exactly: make the table point on the new location)
	notes = tmp;	
}
