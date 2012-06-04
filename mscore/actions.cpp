//=============================================================================
//  MuseScore
//  Linux Music Score Editor
//  $Id: actions.cpp 5657 2012-05-21 15:46:06Z lasconic $
//
//  Copyright (C) 2002-2011 Werner Schweer and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//=============================================================================

#include "config.h"
#include "musescore.h"
#include "libmscore/score.h"      // states
#include "icons.h"
#include "shortcut.h"

//---------------------------------------------------------
//    initial list of shortcuts
//---------------------------------------------------------

Shortcut Shortcut::sc[] = {
      Shortcut(
         STATE_ALL,
         0,
         "local-help",
         QT_TRANSLATE_NOOP("action","Local handbook"),            // Appears in Edit > Preferences > Shortcuts
         QT_TRANSLATE_NOOP("action","Local &Handbook..."),        // Appears in menu
         QT_TRANSLATE_NOOP("action","Show local handbook")        // Appears if you use Help > What's This?
         ),

      Shortcut(
         STATE_DISABLED | STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         0,
         "file-open",
         QT_TRANSLATE_NOOP("action","File open"),
         QT_TRANSLATE_NOOP("action","&Open..."),
         QT_TRANSLATE_NOOP("action","Load score from file"),
         fileOpen_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         0,
         "file-save",
         QT_TRANSLATE_NOOP("action","File save"),
         QT_TRANSLATE_NOOP("action","&Save"),
         QT_TRANSLATE_NOOP("action","Save score to file"),
          fileSave_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         A_SCORE,
         "file-save-as",
         QT_TRANSLATE_NOOP("action","File save as"),
         QT_TRANSLATE_NOOP("action","Save &As..."),
         QT_TRANSLATE_NOOP("action","Save score under a new file name"),
         fileSaveAs_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         A_SCORE,
         "file-save-selection",
         QT_TRANSLATE_NOOP("action","Save Selection"),
         QT_TRANSLATE_NOOP("action","Save Selection..."),
         QT_TRANSLATE_NOOP("action","Save current selection as new score"),
         fileSaveAs_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         A_SCORE,
         "file-save-a-copy",
         QT_TRANSLATE_NOOP("action","File save a copy"),
         QT_TRANSLATE_NOOP("action","Save a Copy..."),
         QT_TRANSLATE_NOOP("action","Save a copy of the score in addition to the current file")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         A_SCORE,
         "file-export",
         QT_TRANSLATE_NOOP("action","Export score"),
         QT_TRANSLATE_NOOP("action","&Export..."),
         QT_TRANSLATE_NOOP("action","Save a copy of the score in various formats"),
         fileSave_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         A_SCORE,
         "file-part-export",
         QT_TRANSLATE_NOOP("action","Export Parts"),
         QT_TRANSLATE_NOOP("action","Export Parts..."),
         QT_TRANSLATE_NOOP("action","Save a copy of the score's parts in various formats"),
         fileSave_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         A_SCORE,
         "file-reload",
         QT_TRANSLATE_NOOP("action","File reload"),
         QT_TRANSLATE_NOOP("action","Reload"),
         QT_TRANSLATE_NOOP("action","Reload score from file")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         0,
         "file-close",
         QT_TRANSLATE_NOOP("action","File close"),
         QT_TRANSLATE_NOOP("action","&Close"),
         QT_TRANSLATE_NOOP("action","Close current score")
         ),
      Shortcut(
         STATE_DISABLED | STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         0,
         "file-new",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","File new"),
         QT_TRANSLATE_NOOP("action","&New..."),
         QT_TRANSLATE_NOOP("action","Create new score"),
          fileNew_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         A_SCORE,
         "print",
         QT_TRANSLATE_NOOP("action","Print"),
         QT_TRANSLATE_NOOP("action","&Print..."),
         QT_TRANSLATE_NOOP("action","Print score"),
          print_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "undo",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Undo"),
         QT_TRANSLATE_NOOP("action","&Undo"),
         QT_TRANSLATE_NOOP("action","Undo last change"),
          undo_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "redo",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Redo"),
         QT_TRANSLATE_NOOP("action","&Redo"),
         QT_TRANSLATE_NOOP("action","Redo last undo"),
          redo_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "cut",
         QT_TRANSLATE_NOOP("action","Cut"),
         QT_TRANSLATE_NOOP("action","Cu&t"),
         QT_TRANSLATE_NOOP("action",""),
          cut_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_FOTO,
         0,
         "copy",
         QT_TRANSLATE_NOOP("action","Copy"),
         QT_TRANSLATE_NOOP("action","&Copy"),
         QT_TRANSLATE_NOOP("action",""),
          copy_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "paste",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Paste"),
         QT_TRANSLATE_NOOP("action","&Paste"),
         QT_TRANSLATE_NOOP("action",""),
          paste_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "instruments",
         QT_TRANSLATE_NOOP("action","Show instruments dialog"),
         QT_TRANSLATE_NOOP("action","&Instruments..."),
         QT_TRANSLATE_NOOP("action","Show instruments dialog")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "note-input",
         QT_TRANSLATE_NOOP("action","Note input mode"),
         QT_TRANSLATE_NOOP("action","&Note Input"),
         QT_TRANSLATE_NOOP("action","Note input mode"),
          noteEntry_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pitch-spell",
         QT_TRANSLATE_NOOP("action","Respell pitches"),
         QT_TRANSLATE_NOOP("action","&Respell Pitches"),
         QT_TRANSLATE_NOOP("action","Respell pitches")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval1",
         QT_TRANSLATE_NOOP("action","Enter unison above"),
         QT_TRANSLATE_NOOP("action","Unison Above"),
         QT_TRANSLATE_NOOP("action","Enter unison above")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval2",
         QT_TRANSLATE_NOOP("action","Enter second above"),
         QT_TRANSLATE_NOOP("action","Second Above"),
         QT_TRANSLATE_NOOP("action","Enter second above")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval3",
         QT_TRANSLATE_NOOP("action","Enter third above"),
         QT_TRANSLATE_NOOP("action","Third Above"),
         QT_TRANSLATE_NOOP("action","Enter third above")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval4",
         QT_TRANSLATE_NOOP("action","Enter fourth above"),
         QT_TRANSLATE_NOOP("action","Fourth Above"),
         QT_TRANSLATE_NOOP("action","Enter fourth above")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval5",
         QT_TRANSLATE_NOOP("action","Enter fifth above"),
         QT_TRANSLATE_NOOP("action","Fifth Above"),
         QT_TRANSLATE_NOOP("action","Enter fifth above")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval6",
         QT_TRANSLATE_NOOP("action","Enter sixth above"),
         QT_TRANSLATE_NOOP("action","Sixth Above"),
         QT_TRANSLATE_NOOP("action","Enter sixth above")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval7",
         QT_TRANSLATE_NOOP("action","Enter seventh above"),
         QT_TRANSLATE_NOOP("action","Seventh Above"),
         QT_TRANSLATE_NOOP("action","Enter seventh above")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval8",
         QT_TRANSLATE_NOOP("action","Enter octave above"),
         QT_TRANSLATE_NOOP("action","Octave Above"),
         QT_TRANSLATE_NOOP("action","Enter octave above")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval9",
         QT_TRANSLATE_NOOP("action","Enter ninth above"),
         QT_TRANSLATE_NOOP("action","Ninth Above"),
         QT_TRANSLATE_NOOP("action","Enter ninth above")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval-2",
         QT_TRANSLATE_NOOP("action","Enter second below"),
         QT_TRANSLATE_NOOP("action","Second Below"),
         QT_TRANSLATE_NOOP("action","Enter second below")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval-3",
         QT_TRANSLATE_NOOP("action","Enter third below"),
         QT_TRANSLATE_NOOP("action","Third Below"),
         QT_TRANSLATE_NOOP("action","Enter third below")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval-4",
         QT_TRANSLATE_NOOP("action","Enter fourth below"),
         QT_TRANSLATE_NOOP("action","Fourth Below"),
         QT_TRANSLATE_NOOP("action","Enter fourth below")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval-5",
         QT_TRANSLATE_NOOP("action","Enter fifth below"),
         QT_TRANSLATE_NOOP("action","Fifth Below"),
         QT_TRANSLATE_NOOP("action","Enter fifth below")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval-6",
         QT_TRANSLATE_NOOP("action","Enter sixth below"),
         QT_TRANSLATE_NOOP("action","Sixth Below"),
         QT_TRANSLATE_NOOP("action","Enter sixth below")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval-7",
         QT_TRANSLATE_NOOP("action","Enter seventh below"),
         QT_TRANSLATE_NOOP("action","Seventh Below"),
         QT_TRANSLATE_NOOP("action","Enter seventh below")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval-8",
         QT_TRANSLATE_NOOP("action","Enter octave below"),
         QT_TRANSLATE_NOOP("action","Octave Below"),
         QT_TRANSLATE_NOOP("action","Enter octave below")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "interval-9",
         QT_TRANSLATE_NOOP("action","Enter ninth below"),
         QT_TRANSLATE_NOOP("action","Ninth Below"),
         QT_TRANSLATE_NOOP("action","Enter ninth below")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "note-a",
         QT_TRANSLATE_NOOP("action","Enter note A"),
         QT_TRANSLATE_NOOP("action","A"),
         QT_TRANSLATE_NOOP("action","Enter note A")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "note-b",
         QT_TRANSLATE_NOOP("action","Enter note B"),
         QT_TRANSLATE_NOOP("action","B"),
         QT_TRANSLATE_NOOP("action","Enter note B")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "note-c",
         QT_TRANSLATE_NOOP("action","Enter note C"),
         QT_TRANSLATE_NOOP("action","C"),
         QT_TRANSLATE_NOOP("action","Enter note C")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "note-d",
         QT_TRANSLATE_NOOP("action","Enter note D"),
         QT_TRANSLATE_NOOP("action","D"),
         QT_TRANSLATE_NOOP("action","Enter note D")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "note-e",
         QT_TRANSLATE_NOOP("action","Enter note E"),
         QT_TRANSLATE_NOOP("action","E"),
         QT_TRANSLATE_NOOP("action","Enter note E")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "note-f",
         QT_TRANSLATE_NOOP("action","Enter note F"),
         QT_TRANSLATE_NOOP("action","F"),
         QT_TRANSLATE_NOOP("action","Enter note F")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "note-g",
         QT_TRANSLATE_NOOP("action","Enter note G"),
         QT_TRANSLATE_NOOP("action","G"),
         QT_TRANSLATE_NOOP("action","Enter note G")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "chord-a",
         QT_TRANSLATE_NOOP("action","Add note A to chord"),
         QT_TRANSLATE_NOOP("action","Add A"),
         QT_TRANSLATE_NOOP("action","Add note A to chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "chord-b",
         QT_TRANSLATE_NOOP("action","Add note B to chord"),
         QT_TRANSLATE_NOOP("action","Add B"),
         QT_TRANSLATE_NOOP("action","Add note B to chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "chord-c",
         QT_TRANSLATE_NOOP("action","Add note C to chord"),
         QT_TRANSLATE_NOOP("action","Add C"),
         QT_TRANSLATE_NOOP("action","Add note C to chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "chord-d",
         QT_TRANSLATE_NOOP("action","Add note D to chord"),
         QT_TRANSLATE_NOOP("action","Add D"),
         QT_TRANSLATE_NOOP("action","Add note D to chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "chord-e",
         QT_TRANSLATE_NOOP("action","Add note E to chord"),
         QT_TRANSLATE_NOOP("action","Add E"),
         QT_TRANSLATE_NOOP("action","Add note E to chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "chord-f",
         QT_TRANSLATE_NOOP("action","Add note F to chord"),
         QT_TRANSLATE_NOOP("action","Add F"),
         QT_TRANSLATE_NOOP("action","Add note F to chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "chord-g",
         QT_TRANSLATE_NOOP("action","Add note G to chord"),
         QT_TRANSLATE_NOOP("action","Add G"),
         QT_TRANSLATE_NOOP("action","Add note G to chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-a",
         QT_TRANSLATE_NOOP("action","Insert note A"),
         QT_TRANSLATE_NOOP("action","Insert A"),
         QT_TRANSLATE_NOOP("action","Insert note A")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-b",
         QT_TRANSLATE_NOOP("action","Insert note B"),
         QT_TRANSLATE_NOOP("action","Insert B"),
         QT_TRANSLATE_NOOP("action","Insert note B")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-c",
         QT_TRANSLATE_NOOP("action","Insert note C"),
         QT_TRANSLATE_NOOP("action","Insert C"),
         QT_TRANSLATE_NOOP("action","Insert note C")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-d",
         QT_TRANSLATE_NOOP("action","Insert note D"),
         QT_TRANSLATE_NOOP("action","Insert D"),
         QT_TRANSLATE_NOOP("action","Insert note D")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-e",
         QT_TRANSLATE_NOOP("action","Insert note E"),
         QT_TRANSLATE_NOOP("action","Insert E"),
         QT_TRANSLATE_NOOP("action","Insert note E")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-f",
         QT_TRANSLATE_NOOP("action","Insert note F"),
         QT_TRANSLATE_NOOP("action","Insert F"),
         QT_TRANSLATE_NOOP("action","Insert note F")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-g",
         QT_TRANSLATE_NOOP("action","Insert note G"),
         QT_TRANSLATE_NOOP("action","Insert G"),
         QT_TRANSLATE_NOOP("action","Insert note G")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "rest",
         QT_TRANSLATE_NOOP("action","Enter rest"),
         QT_TRANSLATE_NOOP("action","Rest"),
         QT_TRANSLATE_NOOP("action","Enter rest"),
          quartrest_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "add-staccato",
         QT_TRANSLATE_NOOP("action","Add staccato"),
         QT_TRANSLATE_NOOP("action","Staccato"),
         QT_TRANSLATE_NOOP("action","Add staccato")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "add-tenuto",
         QT_TRANSLATE_NOOP("action","Add tenuto"),
         QT_TRANSLATE_NOOP("action","Tenuto"),
         QT_TRANSLATE_NOOP("action","Add tenuto")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "add-trill",
         QT_TRANSLATE_NOOP("action","Add trill"),
         QT_TRANSLATE_NOOP("action","Trill"),
         QT_TRANSLATE_NOOP("action","Add trill")
         ),
      Shortcut(
        STATE_NORMAL | STATE_NOTE_ENTRY,
        A_CMD,
        "add-marcato",
        QT_TRANSLATE_NOOP("action","Add marcato"),
        QT_TRANSLATE_NOOP("action","Marcato"),
        QT_TRANSLATE_NOOP("action","Add marcato")
        ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "stretch+",
         QT_TRANSLATE_NOOP("action","More stretch"),
         QT_TRANSLATE_NOOP("action","Add &More Stretch"),
         QT_TRANSLATE_NOOP("action","Add more stretch to selected measure")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "stretch-",
         QT_TRANSLATE_NOOP("action","Less stretch"),
         QT_TRANSLATE_NOOP("action","Add &Less Stretch"),
         QT_TRANSLATE_NOOP("action","Add less stretch to selected measure")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "reset-beammode",
         QT_TRANSLATE_NOOP("action","Reset Beam Mode"),
         QT_TRANSLATE_NOOP("action","Reset &Beam Mode"),
         QT_TRANSLATE_NOOP("action","Reset beam mode of selected measures")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "flip",
         QT_TRANSLATE_NOOP("action","Flip direction"),
         QT_TRANSLATE_NOOP("action","Flip Direction"),
         QT_TRANSLATE_NOOP("action","Flip direction"),
          flip_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pitch-up",
         QT_TRANSLATE_NOOP("action","Pitch up"),
         QT_TRANSLATE_NOOP("action","Up"),
         QT_TRANSLATE_NOOP("action","Pitch up")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pitch-up-diatonic",
         QT_TRANSLATE_NOOP("action","Diatonic pitch up"),
         QT_TRANSLATE_NOOP("action","Diatonic up"),
         QT_TRANSLATE_NOOP("action","Diatonic pitch up")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pitch-up-octave",
         QT_TRANSLATE_NOOP("action","Pitch up octave"),
         QT_TRANSLATE_NOOP("action","Up Octave"),
         QT_TRANSLATE_NOOP("action","Pitch up by an octave")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "up-chord",
         QT_TRANSLATE_NOOP("action","Go to higher pitched note in chord"),
         QT_TRANSLATE_NOOP("action","Up Note in Chord"),
         QT_TRANSLATE_NOOP("action","Go to higher pitched note in chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "top-chord",
         QT_TRANSLATE_NOOP("action","Go to top note in chord"),
         QT_TRANSLATE_NOOP("action","Top Note in Chord"),
         QT_TRANSLATE_NOOP("action","Go to top note in chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "move-up",
         QT_TRANSLATE_NOOP("action","Move up"),
         QT_TRANSLATE_NOOP("action","up+shift+ctrl"),
         QT_TRANSLATE_NOOP("action","up+shift+ctrl")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pitch-down",
         QT_TRANSLATE_NOOP("action","Pitch down"),
         QT_TRANSLATE_NOOP("action","Down"),
         QT_TRANSLATE_NOOP("action","Pitch down")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pitch-down-diatonic",
         QT_TRANSLATE_NOOP("action","Diatonic pitch down"),
         QT_TRANSLATE_NOOP("action","Diatonic down"),
         QT_TRANSLATE_NOOP("action","Diatonic pitch down")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pitch-down-octave",
         QT_TRANSLATE_NOOP("action","Pitch down octave"),
         QT_TRANSLATE_NOOP("action","Down octave"),
         QT_TRANSLATE_NOOP("action","Pitch down by an octave")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "down-chord",
         QT_TRANSLATE_NOOP("action","Go to lower pitched note in chord"),
         QT_TRANSLATE_NOOP("action","Down Note in Chord"),
         QT_TRANSLATE_NOOP("action","Go to lower pitched note in chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "bottom-chord",
         QT_TRANSLATE_NOOP("action","Go to bottom note in chord"),
         QT_TRANSLATE_NOOP("action","Bottom Note in Chord"),
         QT_TRANSLATE_NOOP("action","Go to bottom note in chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "move-down",
         QT_TRANSLATE_NOOP("action","Move down"),
         QT_TRANSLATE_NOOP("action","down+shift+ctrl"),
         QT_TRANSLATE_NOOP("action","down+shift+ctrl")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "prev-chord",
         QT_TRANSLATE_NOOP("action","Previous chord"),
         QT_TRANSLATE_NOOP("action","Previous Chord"),
         QT_TRANSLATE_NOOP("action","Previous chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "prev-measure",
         QT_TRANSLATE_NOOP("action","Previous measure"),
         QT_TRANSLATE_NOOP("action","Previous Measure"),
         QT_TRANSLATE_NOOP("action","Previous measure")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "next-chord",
         QT_TRANSLATE_NOOP("action","Next chord"),
         QT_TRANSLATE_NOOP("action","Next Chord"),
         QT_TRANSLATE_NOOP("action","Next chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "next-measure",
         QT_TRANSLATE_NOOP("action","Next measure"),
         QT_TRANSLATE_NOOP("action","Next Measure"),
         QT_TRANSLATE_NOOP("action","Next measure")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "select-prev-chord",
         QT_TRANSLATE_NOOP("action","Add previous chord to selection"),
         QT_TRANSLATE_NOOP("action","left+shift"),
         QT_TRANSLATE_NOOP("action","left+shift")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "select-prev-measure",
         QT_TRANSLATE_NOOP("action","Select to beginning of measure"),
         QT_TRANSLATE_NOOP("action","left+ctrl"),
         QT_TRANSLATE_NOOP("action","left+ctrl")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "select-next-chord",
         QT_TRANSLATE_NOOP("action","Add next chord to selection"),
         QT_TRANSLATE_NOOP("action","right+shift"),
         QT_TRANSLATE_NOOP("action","right+shift")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "select-section",
         QT_TRANSLATE_NOOP("action","Select Section"),
         QT_TRANSLATE_NOOP("action","Select Section"),
         QT_TRANSLATE_NOOP("action","select section")
         ),
      Shortcut(
         STATE_NOTE_ENTRY,
         0,
         "move-right",
         QT_TRANSLATE_NOOP("action","Move chord/rest right"),
         QT_TRANSLATE_NOOP("action","Move chord/rest right"),
         QT_TRANSLATE_NOOP("action","Move chord/rest right")
         ),
      Shortcut(
         STATE_NOTE_ENTRY,
         0,
         "move-left",
         QT_TRANSLATE_NOOP("action","Move chord/rest left"),
         QT_TRANSLATE_NOOP("action","Move chord/rest left"),
         QT_TRANSLATE_NOOP("action","Move chord/rest left")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "select-next-measure",
         QT_TRANSLATE_NOOP("action","Select to end of measure"),
         QT_TRANSLATE_NOOP("action","right+ctrl+shift"),
         QT_TRANSLATE_NOOP("action","right+ctrl+shift")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "select-begin-line",
         QT_TRANSLATE_NOOP("action","Select to beginning of line"),
         QT_TRANSLATE_NOOP("action","shift+home"),
         QT_TRANSLATE_NOOP("action","shift+home")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "select-end-line",
         QT_TRANSLATE_NOOP("action","Select to end of line"),
         QT_TRANSLATE_NOOP("action","shift+end"),
         QT_TRANSLATE_NOOP("action","shift+end")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "select-begin-score",
         QT_TRANSLATE_NOOP("action","Select to beginning of score"),
         QT_TRANSLATE_NOOP("action","ctrl+shift+home"),
         QT_TRANSLATE_NOOP("action","ctrl+shift+home")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "select-end-score",
         QT_TRANSLATE_NOOP("action","Select to end of score"),
         QT_TRANSLATE_NOOP("action","ctrl+shift+end"),
         QT_TRANSLATE_NOOP("action","ctrl+shift+end")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "select-staff-above",
         QT_TRANSLATE_NOOP("action","Add staff above to selection"),
         QT_TRANSLATE_NOOP("action","Add staff above to selection"),
         QT_TRANSLATE_NOOP("action","Add staff above to selection")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "select-staff-below",
         QT_TRANSLATE_NOOP("action","Add staff below to selection"),
         QT_TRANSLATE_NOOP("action","Add staff below to selection"),
         QT_TRANSLATE_NOOP("action","Add staff below to selection")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "page-prev",
         QT_TRANSLATE_NOOP("action","Page: previous"),
         QT_TRANSLATE_NOOP("action",""),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "page-next",
         QT_TRANSLATE_NOOP("action","Page: next"),
         QT_TRANSLATE_NOOP("action",""),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "page-top",
         QT_TRANSLATE_NOOP("action","Page: top"),
         QT_TRANSLATE_NOOP("action",""),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "page-end",
         QT_TRANSLATE_NOOP("action","Page: end"),
         QT_TRANSLATE_NOOP("action",""),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "add-slur",
         QT_TRANSLATE_NOOP("action","Add slur"),
         QT_TRANSLATE_NOOP("action",""),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "add-hairpin",
         QT_TRANSLATE_NOOP("action","Crescendo"),
         QT_TRANSLATE_NOOP("action",""),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "add-hairpin-reverse",
         QT_TRANSLATE_NOOP("action","Decrescendo"),
         QT_TRANSLATE_NOOP("action",""),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY | STATE_SEARCH | STATE_FOTO,
         0,
         "escape",
         QT_TRANSLATE_NOOP("action","Escape"),
         QT_TRANSLATE_NOOP("action",""),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "delete",
         QT_TRANSLATE_NOOP("action","Delete"),
         QT_TRANSLATE_NOOP("action","Delete"),
         QT_TRANSLATE_NOOP("action","Delete contents of the selected measures")
         ),
      Shortcut(
         STATE_NORMAL,
         A_CMD,
         "time-delete",
         QT_TRANSLATE_NOOP("action","Timewise delete"),
         QT_TRANSLATE_NOOP("action","Timewise Delete"),
         QT_TRANSLATE_NOOP("action","Delete element and duration")
         ),
      Shortcut(
         STATE_NORMAL,
         A_CMD,
         "delete-measures",
         QT_TRANSLATE_NOOP("action","Delete selected measures"),
         QT_TRANSLATE_NOOP("action","Delete Selected Measures"),
         QT_TRANSLATE_NOOP("action","Delete selected measures")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "append-measure",
         QT_TRANSLATE_NOOP("action","Append one measure"),      // Appears in Edit > Preferences > Shortcuts
         QT_TRANSLATE_NOOP("action","Append One Measure")       // Appears in menu
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "append-measures",
         QT_TRANSLATE_NOOP("action","Append measures"),
         QT_TRANSLATE_NOOP("action","Append Measures...")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-measure",
         QT_TRANSLATE_NOOP("action","Insert one measure"),
         QT_TRANSLATE_NOOP("action","Insert One Measure")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-measures",
         QT_TRANSLATE_NOOP("action","Insert measures"),
         QT_TRANSLATE_NOOP("action","Insert Measures...")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-hbox",
         QT_TRANSLATE_NOOP("action","Insert horizontal frame"),
         QT_TRANSLATE_NOOP("action","Insert Horizontal Frame")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-textframe",
         QT_TRANSLATE_NOOP("action","Insert text frame"),
         QT_TRANSLATE_NOOP("action","Insert Text Frame")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "append-textframe",
         QT_TRANSLATE_NOOP("action","Append text frame"),
         QT_TRANSLATE_NOOP("action","Append Text Frame")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-fretframe",
         QT_TRANSLATE_NOOP("action","Insert fret diagram frame"),
         QT_TRANSLATE_NOOP("action","Insert Fret Diagram Frame")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "insert-vbox",
         QT_TRANSLATE_NOOP("action","Insert vertical frame"),
         QT_TRANSLATE_NOOP("action","Insert Vertical Frame")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "append-hbox",
         QT_TRANSLATE_NOOP("action","Append horizontal frame"),
         QT_TRANSLATE_NOOP("action","Append Horizontal Frame")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "append-vbox",
         QT_TRANSLATE_NOOP("action","Append vertical frame"),
         QT_TRANSLATE_NOOP("action","Append Vertical Frame")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "duplet",
         QT_TRANSLATE_NOOP("action","Duplet"),
         QT_TRANSLATE_NOOP("action","Duplet")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "triplet",
         QT_TRANSLATE_NOOP("action","Triplet"),
         QT_TRANSLATE_NOOP("action","Triplet")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "quadruplet",
         QT_TRANSLATE_NOOP("action","Quadruplet"),
         QT_TRANSLATE_NOOP("action","Quadruplet")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "quintuplet",
         QT_TRANSLATE_NOOP("action","Quintuplet"),
         QT_TRANSLATE_NOOP("action","Quintuplet")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "sextuplet",
         QT_TRANSLATE_NOOP("action","Sextuplet"),
         QT_TRANSLATE_NOOP("action","Sextuplet")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "septuplet",
         QT_TRANSLATE_NOOP("action","Septuplet"),
         QT_TRANSLATE_NOOP("action","Septuplet")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "octuplet",
         QT_TRANSLATE_NOOP("action","Octuplet"),
         QT_TRANSLATE_NOOP("action","Octuplet")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "nonuplet",
         QT_TRANSLATE_NOOP("action","Nonuplet"),
         QT_TRANSLATE_NOOP("action","Nonuplet")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "tuplet-dialog",
         QT_TRANSLATE_NOOP("action","Other tuplets"),
         QT_TRANSLATE_NOOP("action","Other...")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "note-longa",
         QT_TRANSLATE_NOOP("action","Note duration: longa"),
         QT_TRANSLATE_NOOP("action","Longa"),
         QT_TRANSLATE_NOOP("action","Longa"),
          longaUp_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "note-breve",
         QT_TRANSLATE_NOOP("action","Note duration: double whole"),
         QT_TRANSLATE_NOOP("action","Double whole note"),
         QT_TRANSLATE_NOOP("action","Double whole note"),
          brevis_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pad-note-1",
         QT_TRANSLATE_NOOP("action","Note duration: whole"),
         QT_TRANSLATE_NOOP("action","Whole note"),
         QT_TRANSLATE_NOOP("action","Whole note"),
          note_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pad-note-2",
         QT_TRANSLATE_NOOP("action","Note duration: half"),
         QT_TRANSLATE_NOOP("action","Half note"),
         QT_TRANSLATE_NOOP("action","Half note"),
          note2_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pad-note-4",
         QT_TRANSLATE_NOOP("action","Note duration: quarter"),
         QT_TRANSLATE_NOOP("action","Quarter note"),
         QT_TRANSLATE_NOOP("action","Quarter note"),
          note4_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pad-note-8",
         QT_TRANSLATE_NOOP("action","Note duration: 8th"),
         QT_TRANSLATE_NOOP("action","8th note"),
         QT_TRANSLATE_NOOP("action","8th note"),
          note8_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pad-note-16",
         QT_TRANSLATE_NOOP("action","Note duration: 16th"),
         QT_TRANSLATE_NOOP("action","16th note"),
         QT_TRANSLATE_NOOP("action","16th note"),
          note16_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pad-note-32",
         QT_TRANSLATE_NOOP("action","Note duration: 32nd"),
         QT_TRANSLATE_NOOP("action","32nd note"),
         QT_TRANSLATE_NOOP("action","32nd note"),
          note32_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pad-note-64",
         QT_TRANSLATE_NOOP("action","Note duration: 64th"),
         QT_TRANSLATE_NOOP("action","64th note"),
         QT_TRANSLATE_NOOP("action","64th note"),
          note64_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pad-note-128",
         QT_TRANSLATE_NOOP("action","Note duration: 128th"),
         QT_TRANSLATE_NOOP("action","128th note"),
         QT_TRANSLATE_NOOP("action","128th note"),
          note128_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pad-dot",
         QT_TRANSLATE_NOOP("action","Note duration: augmentation dot"),
         QT_TRANSLATE_NOOP("action","Augmentation dot"),
         QT_TRANSLATE_NOOP("action","Augmentation dot"),
          dot_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pad-dotdot",
         QT_TRANSLATE_NOOP("action","Note duration: double augmentation dot"),
         QT_TRANSLATE_NOOP("action","Double augmentation dot"),
         QT_TRANSLATE_NOOP("action","Double augmentation dot"),
          dotdot_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "tie",
         QT_TRANSLATE_NOOP("action","Note duration: tie"),
         QT_TRANSLATE_NOOP("action","Tie"),
         QT_TRANSLATE_NOOP("action","Tie"),
         tie_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "pad-rest",
         QT_TRANSLATE_NOOP("action","Note entry: rest"),
         QT_TRANSLATE_NOOP("action","Rest"),
         QT_TRANSLATE_NOOP("action","Rest"),
          quartrest_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "sharp2",
         QT_TRANSLATE_NOOP("action","Note entry: double sharp"),
         QT_TRANSLATE_NOOP("action","Double sharp"),
         QT_TRANSLATE_NOOP("action","Double sharp"),
          sharpsharp_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "sharp",
         QT_TRANSLATE_NOOP("action","Note entry: sharp"),
         QT_TRANSLATE_NOOP("action","Sharp"),
         QT_TRANSLATE_NOOP("action","Sharp"),
          sharp_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "nat",
         QT_TRANSLATE_NOOP("action","Note entry: natural"),
         QT_TRANSLATE_NOOP("action","Natural"),
         QT_TRANSLATE_NOOP("action","Natural"),
          natural_ICON
         ),
       Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "flat",
         QT_TRANSLATE_NOOP("action","Note entry: flat"),
         QT_TRANSLATE_NOOP("action","Flat"),
         QT_TRANSLATE_NOOP("action","Flat"),
          flat_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "flat2",
         QT_TRANSLATE_NOOP("action","Note entry: double flat"),
         QT_TRANSLATE_NOOP("action","Double flat"),
         QT_TRANSLATE_NOOP("action","Double flat"),
          flatflat_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "acciaccatura",
         QT_TRANSLATE_NOOP("action","Acciaccatura"),
         QT_TRANSLATE_NOOP("action","Acciaccatura"),
         QT_TRANSLATE_NOOP("action","Acciaccatura"),
          acciaccatura_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "appoggiatura",
         QT_TRANSLATE_NOOP("action","Appoggiatura"),
         QT_TRANSLATE_NOOP("action","Appoggiatura"),
         QT_TRANSLATE_NOOP("action","Appoggiatura"),
          appoggiatura_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
	 /* no stroke: 4th*/
        "grace4",
        QT_TRANSLATE_NOOP("action","Grace: quarter"),
        QT_TRANSLATE_NOOP("action","Grace: quarter"),
        QT_TRANSLATE_NOOP("action","Grace: quarter"),
         grace4_ICON
        ),
     Shortcut(
        STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
      /* no stroke: 16th*/
        "grace16",
        QT_TRANSLATE_NOOP("action","Grace: 16th"),
        QT_TRANSLATE_NOOP("action","Grace: 16th"),
        QT_TRANSLATE_NOOP("action","Grace: 16th"),
         grace16_ICON
        ),
     Shortcut(
        STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
      /* no stroke: 32th*/
        "grace32",
        QT_TRANSLATE_NOOP("action","Grace: 32nd"),
        QT_TRANSLATE_NOOP("action","Grace: 32nd"),
        QT_TRANSLATE_NOOP("action","Grace: 32nd"),
         grace32_ICON
        ),
     Shortcut(
        STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
        "grace8b",
        QT_TRANSLATE_NOOP("action","Grace: 8nd after"),
        QT_TRANSLATE_NOOP("action","Grace: 8nd after"),
        QT_TRANSLATE_NOOP("action","Grace: 8nd after"),
         grace8b_ICON
        ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "voice-1",
         QT_TRANSLATE_NOOP("action","Voice 1"),
         QT_TRANSLATE_NOOP("action","Voice 1"),
         QT_TRANSLATE_NOOP("action","Voice 1"),
          voice1_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "voice-2",
         QT_TRANSLATE_NOOP("action","Voice 2"),
         QT_TRANSLATE_NOOP("action","Voice 2"),
         QT_TRANSLATE_NOOP("action","Voice 2"),
          voice2_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "voice-3",
         QT_TRANSLATE_NOOP("action","Voice 3"),
         QT_TRANSLATE_NOOP("action","Voice 3"),
         QT_TRANSLATE_NOOP("action","Voice 3"),
          voice3_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "voice-4",
         QT_TRANSLATE_NOOP("action","Voice 4"),
         QT_TRANSLATE_NOOP("action","Voice 4"),
         QT_TRANSLATE_NOOP("action","Voice 4"),
          voice4_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "midi-on",
         QT_TRANSLATE_NOOP("action","MIDI input"),
         QT_TRANSLATE_NOOP("action","Enable MIDI input"),
         QT_TRANSLATE_NOOP("action","Enable MIDI input"),
          midiin_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "sound-on",
         QT_TRANSLATE_NOOP("action","Editing sound on"),
         QT_TRANSLATE_NOOP("action","Enable sound while editing"),
         QT_TRANSLATE_NOOP("action","Enable sound while editing"),
          speaker_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "beam-start",
         QT_TRANSLATE_NOOP("action","Beam start"),
         QT_TRANSLATE_NOOP("action","Beam start"),
         QT_TRANSLATE_NOOP("action","Beam start"),
          sbeam_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "beam-mid",
         QT_TRANSLATE_NOOP("action","Beam middle"),
         QT_TRANSLATE_NOOP("action","Beam middle"),
         QT_TRANSLATE_NOOP("action","Beam middle"),
          mbeam_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "no-beam",
         QT_TRANSLATE_NOOP("action","No beam"),
         QT_TRANSLATE_NOOP("action","No beam"),
         QT_TRANSLATE_NOOP("action","No beam"),
          nbeam_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "beam32",
         QT_TRANSLATE_NOOP("action","Beam 32nd sub"),
         QT_TRANSLATE_NOOP("action","Beam 32nd sub"),
         QT_TRANSLATE_NOOP("action","Beam 32nd sub"),
          beam32_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "beam64",
         QT_TRANSLATE_NOOP("action","Beam 64th sub"),
         QT_TRANSLATE_NOOP("action","Beam 64th sub"),
         QT_TRANSLATE_NOOP("action","Beam 64th sub"),
          beam64_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "auto-beam",
         QT_TRANSLATE_NOOP("action","Auto beam"),
         QT_TRANSLATE_NOOP("action","Auto beam"),
         QT_TRANSLATE_NOOP("action","Auto beam"),
          abeam_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "fbeam1",
         QT_TRANSLATE_NOOP("action","Feathered beam, slower"),
         QT_TRANSLATE_NOOP("action","Feathered Beam, Slower"),
         QT_TRANSLATE_NOOP("action","Feathered beam, slower"),
          fbeam1_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "fbeam2",
         QT_TRANSLATE_NOOP("action","Feathered beam, faster"),
         QT_TRANSLATE_NOOP("action","Feathered Beam, Faster"),
         QT_TRANSLATE_NOOP("action","Feathered beam, faster"),
          fbeam2_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         0,
         "toggle-palette",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Palette"),
         QT_TRANSLATE_NOOP("action","Palette"),
         QT_TRANSLATE_NOOP("action","Palette")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         0,
         "toggle-playpanel",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Play panel"),
         QT_TRANSLATE_NOOP("action","Play Panel"),
         QT_TRANSLATE_NOOP("action","Play panel")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         0,
         "toggle-navigator",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Navigator"),
         QT_TRANSLATE_NOOP("action","Navigator"),
         QT_TRANSLATE_NOOP("action","Navigator")
         ),
      Shortcut(
#ifdef Q_WS_MAC
         //Avoid conflict with M in text
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
#else
	   STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
#endif
         0,
         "toggle-mixer",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Mixer"),
         QT_TRANSLATE_NOOP("action","Mixer"),
         QT_TRANSLATE_NOOP("action","Mixer")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "toggle-transport",
         QT_TRANSLATE_NOOP("action","Transport toolbar"),
         QT_TRANSLATE_NOOP("action","Transport"),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "toggle-noteinput",
         QT_TRANSLATE_NOOP("action","Note input toolbar"),
         QT_TRANSLATE_NOOP("action","Note Input"),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "toggle-statusbar",
         QT_TRANSLATE_NOOP("action","Status bar"),
         QT_TRANSLATE_NOOP("action","Status Bar"),
         QT_TRANSLATE_NOOP("action","Status bar")
         ),

      Shortcut(
         STATE_DISABLED | STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY | STATE_FOTO,
         0,
         "quit",
         QT_TRANSLATE_NOOP("action","Quit"),
         QT_TRANSLATE_NOOP("action","Quit"),
         QT_TRANSLATE_NOOP("action","Quit"),
          exit_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "mag",
         QT_TRANSLATE_NOOP("action","Zoom canvas"),
         QT_TRANSLATE_NOOP("action","Zoom Canvas"),
         QT_TRANSLATE_NOOP("action","Zoom canvas"),
          viewmag_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "lyrics",
         QT_TRANSLATE_NOOP("action","Lyrics"),
         QT_TRANSLATE_NOOP("action","Lyrics"),
         QT_TRANSLATE_NOOP("action","Lyrics")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "tempo",
         QT_TRANSLATE_NOOP("action","Tempo"),
         QT_TRANSLATE_NOOP("action","Tempo..."),
         QT_TRANSLATE_NOOP("action","Tempo")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "system-text",
         QT_TRANSLATE_NOOP("action","Add system text"),
         QT_TRANSLATE_NOOP("action","System Text"),
         QT_TRANSLATE_NOOP("action","Add system text")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "staff-text",
         QT_TRANSLATE_NOOP("action","Add staff text"),
         QT_TRANSLATE_NOOP("action","Staff Text"),
         QT_TRANSLATE_NOOP("action","Add staff text")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "frame-text",
         QT_TRANSLATE_NOOP("action","Add text"),
         QT_TRANSLATE_NOOP("action","Frame Text"),
         QT_TRANSLATE_NOOP("action","Add text")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "title-text",
         QT_TRANSLATE_NOOP("action","Add title text"),
         QT_TRANSLATE_NOOP("action","Title"),
         QT_TRANSLATE_NOOP("action","Add title text")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "subtitle-text",
         QT_TRANSLATE_NOOP("action","Add subtitle text"),
         QT_TRANSLATE_NOOP("action","Subtitle"),
         QT_TRANSLATE_NOOP("action","Add subtitle text")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "composer-text",
         QT_TRANSLATE_NOOP("action","Add composer text"),
         QT_TRANSLATE_NOOP("action","Composer"),
         QT_TRANSLATE_NOOP("action","Add composer text")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "poet-text",
         QT_TRANSLATE_NOOP("action","Add lyricist text"),
         QT_TRANSLATE_NOOP("action","Lyricist"),
         QT_TRANSLATE_NOOP("action","Add lyricist text")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "chord-text",
         QT_TRANSLATE_NOOP("action","Add chord name"),
         QT_TRANSLATE_NOOP("action","Chord Name"),
         QT_TRANSLATE_NOOP("action","Add chord name")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "harmony-properties",
         QT_TRANSLATE_NOOP("action","Show harmony properties for chord"),
         QT_TRANSLATE_NOOP("action","Harmony Properties"),
         QT_TRANSLATE_NOOP("action","Show harmony properties for chord")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "rehearsalmark-text",
         QT_TRANSLATE_NOOP("action","Add rehearsal mark"),
         QT_TRANSLATE_NOOP("action","Rehearsal Mark"),
         QT_TRANSLATE_NOOP("action","Add rehearsal mark")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "picture",
         QT_TRANSLATE_NOOP("action","Add picture"),
         QT_TRANSLATE_NOOP("action","Picture"),
         QT_TRANSLATE_NOOP("action","Add picture")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         0,
         "play",
         QT_TRANSLATE_NOOP("action","Player play"),
         QT_TRANSLATE_NOOP("action","Play"),
         QT_TRANSLATE_NOOP("action","Start or stop playback"),
          play_ICON
         ),
      Shortcut(
         STATE_PLAY,
         0,
         "play-prev-chord",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Previous chord"),
         QT_TRANSLATE_NOOP("action","Previous chord"),
         QT_TRANSLATE_NOOP("action","Previous chord")
         ),
      Shortcut(
         STATE_PLAY,
         0,
         "play-prev-measure",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Previous measure"),
         QT_TRANSLATE_NOOP("action","Previous measure"),
         QT_TRANSLATE_NOOP("action","Previous measure")
         ),
      Shortcut(
         STATE_PLAY,
         0,
         "play-next-chord",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Next chord"),
         QT_TRANSLATE_NOOP("action","Next chord"),
         QT_TRANSLATE_NOOP("action","Next chord")
         ),
      Shortcut(
         STATE_PLAY,
         0,
         "play-next-measure",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Next measure"),
         QT_TRANSLATE_NOOP("action","Next measure"),
         QT_TRANSLATE_NOOP("action","Next measure")
         ),
      Shortcut(
         STATE_PLAY,
         0,
         "seek-begin",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Player seek to begin"),
         QT_TRANSLATE_NOOP("action",""),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         0,
         "rewind",
         QT_TRANSLATE_NOOP("action","Player rewind"),
         QT_TRANSLATE_NOOP("action","Rewind"),
         QT_TRANSLATE_NOOP("action","Rewind to start position"),
          start_ICON
         ),
      Shortcut(
         STATE_PLAY,
         0,
         "seek-end",
         QT_TRANSLATE_NOOP("action","Player seek to end"),
         QT_TRANSLATE_NOOP("action",""),
         QT_TRANSLATE_NOOP("action","")
         ),
      Shortcut(
         STATE_NORMAL,
         A_SCORE,
         "repeat",
         QT_TRANSLATE_NOOP("action","Play repeats on/off"),
         QT_TRANSLATE_NOOP("action","Repeat"),
         QT_TRANSLATE_NOOP("action","Play repeats on/off"),
          repeat_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         A_SCORE,
         "pan",
         QT_TRANSLATE_NOOP("action","Pan score while playing on/off"),
         QT_TRANSLATE_NOOP("action","Pan"),
         QT_TRANSLATE_NOOP("action","Pan score while playing on/off"),
          pan_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         A_SCORE,
         "load-style",
         QT_TRANSLATE_NOOP("action","Load style"),
         QT_TRANSLATE_NOOP("action","&Load Style..."),
         QT_TRANSLATE_NOOP("action","Load style"),
          fileOpen_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         A_SCORE,
         "save-style",
         QT_TRANSLATE_NOOP("action","Save style"),
         QT_TRANSLATE_NOOP("action","&Save Style..."),
         QT_TRANSLATE_NOOP("action","Save style"),
          fileSave_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         A_SCORE,
         "save-default-style",
         QT_TRANSLATE_NOOP("action","Save style as default"),
         QT_TRANSLATE_NOOP("action","Save Style As &Default..."),
         QT_TRANSLATE_NOOP("action","Save style as default"),
          fileSave_ICON
         ),
      Shortcut (
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         A_CMD,
         "select-all",
         QT_TRANSLATE_NOOP("action","Select all"),
         QT_TRANSLATE_NOOP("action","Select A&ll"),
         QT_TRANSLATE_NOOP("action","Select all")
         ),
      Shortcut (
         STATE_NORMAL,
         A_CMD,
         "transpose",
         QT_TRANSLATE_NOOP("action","Transpose"),
         QT_TRANSLATE_NOOP("action","&Transpose..."),
         QT_TRANSLATE_NOOP("action","Transpose")
         ),
      Shortcut (
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "clef-violin",
         QT_TRANSLATE_NOOP("action","Violin clef"),
         QT_TRANSLATE_NOOP("action","Violin Clef"),
         QT_TRANSLATE_NOOP("action","Violin clef")
         ),
      Shortcut (
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "clef-bass",
         QT_TRANSLATE_NOOP("action","Bass clef"),
         QT_TRANSLATE_NOOP("action","Bass Clef"),
         QT_TRANSLATE_NOOP("action","Bass clef")
         ),
      Shortcut (
         STATE_NORMAL,
         A_CMD,
         "voice-x12",
         QT_TRANSLATE_NOOP("action","Exchange Voice 1-2"),
         QT_TRANSLATE_NOOP("action","Exchange Voice 1-2"),
         QT_TRANSLATE_NOOP("action","Exchange voice 1-2")
         ),
      Shortcut (
         STATE_NORMAL,
         A_CMD,
         "voice-x13",
         QT_TRANSLATE_NOOP("action","Exchange voice 1-3"),
         QT_TRANSLATE_NOOP("action","Exchange Voice 1-3"),
         QT_TRANSLATE_NOOP("action","Exchange voice 1-3")
         ),
      Shortcut (
         STATE_NORMAL,
         A_CMD,
         "voice-x14",
         QT_TRANSLATE_NOOP("action","Exchange voice 1-4"),
         QT_TRANSLATE_NOOP("action","Exchange Voice 1-4"),
         QT_TRANSLATE_NOOP("action","Exchange voice 1-4")
         ),
      Shortcut (
         STATE_NORMAL,
         A_CMD,
         "voice-x23",
         QT_TRANSLATE_NOOP("action","Exchange voice 2-3"),
         QT_TRANSLATE_NOOP("action","Exchange Voice 2-3"),
         QT_TRANSLATE_NOOP("action","Exchange voice 2-3")
         ),
      Shortcut (
         STATE_NORMAL,
         A_CMD,
         "voice-x24",
         QT_TRANSLATE_NOOP("action","Exchange voice 2-4"),
         QT_TRANSLATE_NOOP("action","Exchange Voice 2-4"),
         QT_TRANSLATE_NOOP("action","Exchange voice 2-4")
         ),
      Shortcut (
         STATE_NORMAL,
         A_CMD,
         "voice-x34",
         QT_TRANSLATE_NOOP("action","Exchange voice 3-4"),
         QT_TRANSLATE_NOOP("action","Exchange Voice 3-4"),
         QT_TRANSLATE_NOOP("action","Exchange voice 3-4")
         ),
      Shortcut (
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "concert-pitch",
         QT_TRANSLATE_NOOP("action","Display in concert pitch"),
         QT_TRANSLATE_NOOP("action","&Concert Pitch"),
         QT_TRANSLATE_NOOP("action","Display in concert pitch")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "repeat-cmd",
         QT_TRANSLATE_NOOP("action","Repeat last command"),
         QT_TRANSLATE_NOOP("action","Repeat Last Command"),
         QT_TRANSLATE_NOOP("action","Repeat last command"),
          fileOpen_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "edit-info",
         QT_TRANSLATE_NOOP("action","Edit score info"),
         QT_TRANSLATE_NOOP("action","&Info..."),
         QT_TRANSLATE_NOOP("action","Edit score info")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "system-break",
         QT_TRANSLATE_NOOP("action","Toggle system break"),
         QT_TRANSLATE_NOOP("action","Toggle System Break"),
         QT_TRANSLATE_NOOP("action","Toggle system break")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "page-break",
         QT_TRANSLATE_NOOP("action","Toggle page break"),
         QT_TRANSLATE_NOOP("action","Toggle Page Break"),
         QT_TRANSLATE_NOOP("action","Toggle page break")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "section-break",
         QT_TRANSLATE_NOOP("action","Toggle section break"),
         QT_TRANSLATE_NOOP("action","Toggle Section Break"),
         QT_TRANSLATE_NOOP("action","Toggle section break")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "edit-element",
         QT_TRANSLATE_NOOP("action","Edit element"),
         QT_TRANSLATE_NOOP("action","Edit Element"),
         QT_TRANSLATE_NOOP("action","Edit element")
         ),
      Shortcut(
         STATE_NORMAL | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "reset",
         QT_TRANSLATE_NOOP("action","Reset user settings"),
         QT_TRANSLATE_NOOP("action","&Reset"),
         QT_TRANSLATE_NOOP("action","Reset user settings")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         0,
         "debugger",
         QT_TRANSLATE_NOOP("action","Show debugger"),
         QT_TRANSLATE_NOOP("action","De&bugger"),
         QT_TRANSLATE_NOOP("action","Show debugger")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "reset-stretch",
         QT_TRANSLATE_NOOP("action","Reset measure stretch"),
         QT_TRANSLATE_NOOP("action","Reset &Stretch"),
         QT_TRANSLATE_NOOP("action","Reset measure stretch")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_SCORE,
         "show-invisible",
         QT_TRANSLATE_NOOP("action","Show invisible"),
         QT_TRANSLATE_NOOP("action","Show Invisible"),
         QT_TRANSLATE_NOOP("action","Show invisible")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_SCORE,
         "show-unprintable",
         QT_TRANSLATE_NOOP("action","Show unprintable"),
         QT_TRANSLATE_NOOP("action","Show Unprintable"),
         QT_TRANSLATE_NOOP("action","Show unprintable")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_SCORE,
         "show-frames",
         QT_TRANSLATE_NOOP("action","Show frames"),
         QT_TRANSLATE_NOOP("action","Show Frames"),
         QT_TRANSLATE_NOOP("action","Show frames")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_SCORE,
         "show-pageborders",
         QT_TRANSLATE_NOOP("action","Show Page Margins"),
         QT_TRANSLATE_NOOP("action","Show Page Margins"),
         QT_TRANSLATE_NOOP("action","Show Page Margins")
         ),
      Shortcut(
         STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "show-keys",
         QT_TRANSLATE_NOOP("action","Insert special characters"),
         QT_TRANSLATE_NOOP("action","Insert Special Characters..."),
         QT_TRANSLATE_NOOP("action","Insert special characters"),
          keys_ICON
         ),
//      Shortcut(
//         STATE_ALL,
//         0,
//         "script-debug",
//         QT_TRANSLATE_NOOP("action","Enable script debugger"),
//         QT_TRANSLATE_NOOP("action","Enable Script Debugger"),
//         QT_TRANSLATE_NOOP("action","Enable script debugger")
//         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "rest-1",
         QT_TRANSLATE_NOOP("action","Note entry: whole rest"),
         QT_TRANSLATE_NOOP("action","Whole rest"),
         QT_TRANSLATE_NOOP("action","Whole rest")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "rest-2",
         QT_TRANSLATE_NOOP("action","Note entry: half rest"),
         QT_TRANSLATE_NOOP("action","Half rest"),
         QT_TRANSLATE_NOOP("action","Half rest")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "rest-4",
         QT_TRANSLATE_NOOP("action","Note entry: quarter rest"),
         QT_TRANSLATE_NOOP("action","Quarter rest"),
         QT_TRANSLATE_NOOP("action","Quarter rest")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "rest-8",
         QT_TRANSLATE_NOOP("action","Note entry: 8th rest"),
         QT_TRANSLATE_NOOP("action","8th rest"),
         QT_TRANSLATE_NOOP("action","8th rest")
         ),
      Shortcut(                     // mapped to undo in note entry mode
         STATE_NOTE_ENTRY,
         0,
         "backspace",
         QT_TRANSLATE_NOOP("action","Backspace"),
         QT_TRANSLATE_NOOP("action","Backspace"),
         QT_TRANSLATE_NOOP("action","Backspace")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_SEARCH,
         0,
         "find",
         QT_TRANSLATE_NOOP("action","Search"),
         QT_TRANSLATE_NOOP("action","&Search"),
         QT_TRANSLATE_NOOP("action","Search")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY,
         0,
         "zoomin",
         QT_TRANSLATE_NOOP("action","Zoom in"),
         QT_TRANSLATE_NOOP("action","Zoom In")
         ),
      Shortcut(
         // conflicts with Ctrl+- in edit mode to enter lyrics hyphen
         // STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,

         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         0,
         "zoomout",
         QT_TRANSLATE_NOOP("action","Zoom out"),
         QT_TRANSLATE_NOOP("action","Zoom Out")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "mirror-note",
         QT_TRANSLATE_NOOP("action","Mirror note head"),
         QT_TRANSLATE_NOOP("action","Mirror note head"),
         QT_TRANSLATE_NOOP("action","Mirror note head"),
         flip_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "edit-style",
         QT_TRANSLATE_NOOP("action","Edit general style"),
         QT_TRANSLATE_NOOP("action","&General..."),
         QT_TRANSLATE_NOOP("action","Edit general style")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "edit-text-style",
         QT_TRANSLATE_NOOP("action","Edit text style"),
         QT_TRANSLATE_NOOP("action","&Text..."),
         QT_TRANSLATE_NOOP("action","Edit text style")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "edit-harmony",
         QT_TRANSLATE_NOOP("action","Edit chord style"),
         QT_TRANSLATE_NOOP("action","&Chords..."),
         QT_TRANSLATE_NOOP("action","Edit chord style")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "select-similar",
         QT_TRANSLATE_NOOP("action","Select all similar elements"),
         QT_TRANSLATE_NOOP("action","All Similar Elements"),
         QT_TRANSLATE_NOOP("action","Select all similar elements")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "select-similar-staff",
         QT_TRANSLATE_NOOP("action","Select all similar elements in same staff"),
         QT_TRANSLATE_NOOP("action","All Similar Elements in Same Staff"),
         QT_TRANSLATE_NOOP("action","Select all similar elements in same staff")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         0,
         "synth-control",
         QT_TRANSLATE_NOOP("action","Synthesizer"),
         QT_TRANSLATE_NOOP("action","Synthesizer"),
         QT_TRANSLATE_NOOP("action","Synthesizer")
         ),
      Shortcut(
         STATE_NOTE_ENTRY,
         A_CMD,
         "double-duration",
         QT_TRANSLATE_NOOP("action","Double duration"),
         QT_TRANSLATE_NOOP("action","Double duration"),
         QT_TRANSLATE_NOOP("action","Double duration")
         ),
      Shortcut(
         STATE_NOTE_ENTRY,
         A_CMD,
         "half-duration",
         QT_TRANSLATE_NOOP("action","Half duration"),
         QT_TRANSLATE_NOOP("action","Half duration"),
         QT_TRANSLATE_NOOP("action","Half duration")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "repeat-sel",
         QT_TRANSLATE_NOOP("action","Repeat selection"),
         QT_TRANSLATE_NOOP("action","Repeat selection"),
         QT_TRANSLATE_NOOP("action","Repeat selection"),
          fileOpen_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         0,
         "follow",
         QT_TRANSLATE_NOOP("action","Follow song"),
         QT_TRANSLATE_NOOP("action","Follow Song"),
         QT_TRANSLATE_NOOP("action","Follow song")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         0,
         "split-h",
         QT_TRANSLATE_NOOP("action","Display documents side by side"),
         QT_TRANSLATE_NOOP("action","Documents Side by Side"),
         QT_TRANSLATE_NOOP("action","Display documents side by side")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         0,
         "split-v",
         QT_TRANSLATE_NOOP("action","Display documents stacked"),
         QT_TRANSLATE_NOOP("action","Documents Stacked"),
         QT_TRANSLATE_NOOP("action","Display documents stacked")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         0,
         "parts",
         QT_TRANSLATE_NOOP("action","Parts"),
         QT_TRANSLATE_NOOP("action","Par&ts..."),
         QT_TRANSLATE_NOOP("action","Manage parts")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "enh-up",
         QT_TRANSLATE_NOOP("action","Enharmonic up"),
         QT_TRANSLATE_NOOP("action","Enharmonic up"),
         QT_TRANSLATE_NOOP("action","Enharmonic up")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "enh-down",
         QT_TRANSLATE_NOOP("action","Enharmonic down"),
         QT_TRANSLATE_NOOP("action","Enharmonic down"),
         QT_TRANSLATE_NOOP("action","Enharmonic down")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "revision",
         QT_TRANSLATE_NOOP("action","Create new revision"),
         QT_TRANSLATE_NOOP("action","Create new revision"),
         QT_TRANSLATE_NOOP("action","Create new revision")
         ),
      Shortcut(
         STATE_NORMAL | STATE_FOTO,
         0,
         "fotomode",
         QT_TRANSLATE_NOOP("action","Toggle foto mode"),
         QT_TRANSLATE_NOOP("action","Toggle foto mode"),
         QT_TRANSLATE_NOOP("action","Toggle foto mode"),
         fotomode_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY,
         0,
         "show-omr",
         QT_TRANSLATE_NOOP("action","Show score image"),
         QT_TRANSLATE_NOOP("action","Show OMR image"),
         QT_TRANSLATE_NOOP("action","Show OMR image")
         ),
      Shortcut(
         STATE_ALL,
         0,
         "fullscreen",
         QT_TRANSLATE_NOOP("action","Full screen"),
         QT_TRANSLATE_NOOP("action","F&ull Screen"),
         QT_TRANSLATE_NOOP("action","F&ull screen")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "hraster",
         QT_TRANSLATE_NOOP("action","Enable horizontal raster"),
         QT_TRANSLATE_NOOP("action","Enable horizontal raster"),
         QT_TRANSLATE_NOOP("action","Enable horizontal raster"),
         hraster_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "vraster",
         QT_TRANSLATE_NOOP("action","Enable vertical raster"),
         QT_TRANSLATE_NOOP("action","Enable vertical raster"),
         QT_TRANSLATE_NOOP("action","Enable vertical raster"),
         vraster_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "config-raster",
         QT_TRANSLATE_NOOP("action","Configure raster"),
         QT_TRANSLATE_NOOP("action","Configure raster"),
         QT_TRANSLATE_NOOP("action","Configure raster")
         ),
      Shortcut(
         STATE_NOTE_ENTRY,
         A_CMD,
         "repitch",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Re-pitch mode"),
         QT_TRANSLATE_NOOP("action","Re-Pitch Mode"),
         QT_TRANSLATE_NOOP("action","Replace pitches without changing rhythms"),
         repitch_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "stack-down",
         QT_TRANSLATE_NOOP("action","Stack down"),
         QT_TRANSLATE_NOOP("action","Stack down"),
         QT_TRANSLATE_NOOP("action","Stack down")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "toogle-piano",
         QT_TRANSLATE_NOOP("action","Piano Keyboard"),
         QT_TRANSLATE_NOOP("action","Piano Keyboard"),
         QT_TRANSLATE_NOOP("action","Piano Keyboard")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY | STATE_FOTO,
         0,
         "media",
         QT_TRANSLATE_NOOP("action","Show media dialog"),
         QT_TRANSLATE_NOOP("action","Additional &Media..."),
         QT_TRANSLATE_NOOP("action","Show media dialog")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "split-measure",
         QT_TRANSLATE_NOOP("action","Split Measure"),
         QT_TRANSLATE_NOOP("action","Split Measure"),
         QT_TRANSLATE_NOOP("action","Split Measure")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "join-measure",
         QT_TRANSLATE_NOOP("action","Join Measure"),
         QT_TRANSLATE_NOOP("action","Join Measure"),
         QT_TRANSLATE_NOOP("action","Join Measure")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY | STATE_FOTO,
         0,
         "page-settings",
         QT_TRANSLATE_NOOP("action","Page Settings"),
         QT_TRANSLATE_NOOP("action","&Page Settings..."),
         QT_TRANSLATE_NOOP("action","Page Settings")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "album",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Album"),
         QT_TRANSLATE_NOOP("action","&Album..."),
         QT_TRANSLATE_NOOP("action","Album")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "layer",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","Layers"),
         QT_TRANSLATE_NOOP("action","&Layers..."),
         QT_TRANSLATE_NOOP("action","Layers")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "next-score",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","next score"),
         QT_TRANSLATE_NOOP("action","next score"),
         QT_TRANSLATE_NOOP("action","next score")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "previous-score",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action","previous score"),
         QT_TRANSLATE_NOOP("action","previous score"),
         QT_TRANSLATE_NOOP("action","previous score")
         ),
      Shortcut(
         STATE_INIT | STATE_DISABLED | STATE_NORMAL | STATE_NOTE_ENTRY | STATE_EDIT | STATE_LYRICS_EDIT | STATE_PLAY | STATE_SEARCH | STATE_FOTO,
         0,
         "musescore-connect",
         Qt::ApplicationShortcut,
         QT_TRANSLATE_NOOP("action", "MuseScore Connect"),
         QT_TRANSLATE_NOOP("action", "MuseScore Connect"),
         QT_TRANSLATE_NOOP("action", "MuseScore Connect"),
         community_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "inspector",
         QT_TRANSLATE_NOOP("action","Show Inspector"),
         QT_TRANSLATE_NOOP("action","Inspector"),
         QT_TRANSLATE_NOOP("action","Show inspector")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "omr",
         QT_TRANSLATE_NOOP("action","Show OMR Panel"),
         QT_TRANSLATE_NOOP("action","OmrPanel"),
         QT_TRANSLATE_NOOP("action","Show OMR PAnel")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY | STATE_PLAY | STATE_EDIT | STATE_LYRICS_EDIT,
         0,
         "metronome",
         QT_TRANSLATE_NOOP("action","Metronome"),
         QT_TRANSLATE_NOOP("action","metronome"),
         QT_TRANSLATE_NOOP("action","toggle metronome"),
         metronome_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         A_CMD,
         "figured-bass",
         QT_TRANSLATE_NOOP("action","Figured Bass"),
         QT_TRANSLATE_NOOP("action","Figured Bass"),
         QT_TRANSLATE_NOOP("action","Figured Bass")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "next-score",
         QT_TRANSLATE_NOOP("action","Next Score"),
         QT_TRANSLATE_NOOP("action","Next Score"),
         QT_TRANSLATE_NOOP("action","Next Score")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "prev-score",
         QT_TRANSLATE_NOOP("action","Previous Score"),
         QT_TRANSLATE_NOOP("action","Previous Score"),
         QT_TRANSLATE_NOOP("action","Previous Score")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "transpose-up",
         QT_TRANSLATE_NOOP("action","Transpose Up"),
         QT_TRANSLATE_NOOP("action","Transpose Up"),
         QT_TRANSLATE_NOOP("action","Transpose Up")
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "transpose-down",
         QT_TRANSLATE_NOOP("action","Transpose Down"),
         QT_TRANSLATE_NOOP("action","Transpose Down"),
         QT_TRANSLATE_NOOP("action","Transpose Down")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "masterpalette",
         QT_TRANSLATE_NOOP("action","Show master palette"),
         QT_TRANSLATE_NOOP("action","Master Palette..."),
         QT_TRANSLATE_NOOP("action","Show master palette")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "vframe",
         QT_TRANSLATE_NOOP("action","Insert vertical frame"),
         QT_TRANSLATE_NOOP("action","Insert Vertical Frame"),
         QT_TRANSLATE_NOOP("action","Insert Vertical Frame"),
         vframe_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "hframe",
         QT_TRANSLATE_NOOP("action","Insert horizontal frame"),
         QT_TRANSLATE_NOOP("action","Insert Horizontal Frame"),
         QT_TRANSLATE_NOOP("action","Insert Horizontal Frame"),
         hframe_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "tframe",
         QT_TRANSLATE_NOOP("action","Insert Text Frame"),
         0,
         0,
         tframe_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "fframe",
         QT_TRANSLATE_NOOP("action","Insert Fret Diagram Frame"),
         0,
         0,
         fframe_ICON
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "measure",
         QT_TRANSLATE_NOOP("action","Insert Measure"),
         0,
         0,
         measure_ICON
         ),
      Shortcut(
         STATE_NORMAL,
         0,
         "viewmode",
         QT_TRANSLATE_NOOP("action","Toggle View Mode")
         ),
      Shortcut(
         STATE_LYRICS_EDIT,
         0,
         "next-lyric",
         QT_TRANSLATE_NOOP("action","next syllable")
         ),
      Shortcut(
         STATE_LYRICS_EDIT,
         0,
         "prev-lyric",
         QT_TRANSLATE_NOOP("action","previous syllable")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "toggle-visible",
         QT_TRANSLATE_NOOP("action","toggle visibility")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "set-visible",
         QT_TRANSLATE_NOOP("action","set visible")
         ),
      Shortcut(
         STATE_NORMAL | STATE_NOTE_ENTRY,
         0,
         "unset-visible",
         QT_TRANSLATE_NOOP("action","set unvisible")
         ),
      // xml==0  marks end of list
      Shortcut(0, 0, 0, 0)
      };

