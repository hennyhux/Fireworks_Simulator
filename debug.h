/*Author: HENRY ZHANG*/
/* this file is mandatory so we can run 3 ways:
 * GRAPHICS set to 1 - suppresses ALL text output, draws instead.
 * GRAPHICS set to 0 - text mode, VERBOSE controls what prints.
 * TEXT has 2 modes: 
 * VERBOSE to 1 to get DEBUG output 
 * VERBOSE to 0 to get only the required text output
 * Do not set TEXT or DEBUG directly; change GRAPHICS and VERBOSE instead.
 */


#define VERBOSE 1	/* 1: all messages, 0: only required messages */
#define TEXT (! GRAPHICS)	/* do not change */
#define GRAPHICS 0	/* 1 for graphics and no text, 0 for text only */

#define DEBUG (VERBOSE && TEXT)	/* do not change this */

