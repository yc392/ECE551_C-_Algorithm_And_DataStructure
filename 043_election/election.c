#include "election.h"

#include <stdio.h>

/*Function for printing error messages*/
void error(char * errorMess) {
  printf("%s", errorMess);
  exit(EXIT_FAILURE);
}

/*This function takes three parameters:
 *   po (which is a pointer to a int)
 *   lineName (a const char where we get the state name)
 *   state (the return value)
 * Copy the state name from the line to the state string variable
 */
state_t getState(int * po, const char * lineName, state_t state) {
  while (lineName[*po] != ':') {
    state.name[*po] = lineName[*po];
    (*po)++;
  }
  if (*po >= MAX_STATE_NAME_LENGTH - 1) {
    //if the state name loger than MAX_STATE_NAME_LENGTH defined, print error and exit
    error("Invalid length of state name");
  }
  state.name[*po] = '\0';  //put the NULL in the end of string
  (*po)++;                 //to the next position
  return state;
}

/*This function takes one parameter:
 *line(which is a const char from the file reading) 
 *Key Variables:
 *int i :current position in the line
 *int j: position of popChar for copying the state population
 *int k: position of voteChar for copying the state electoralVotes  
 *char * popChar :store the state population as string 
 *char * voteChar :store the state electoralVotes as string 
 *Traverse the line char by char and store the useful imformation to variables 
*/
state_t parseLine(const char * line) {
  state_t state;
  state.electoralVotes = 0;  //initializing the state
  state.population = 0;
  int i = 0;
  int * position = &i;  //pointer to int for updating position
  int j = 0;
  int k = 0;
  char * popChar = NULL;
  char * voteChar = NULL;

  state = getState(position, line, state);  //function use

  while (line[i] != ':') {
    //After the first ':',it must be the number or whitespace(no sure it is ok). No more letters
    if ((line[i] >= '0' && line[i] <= '9') || line[i] == ' ') {
      popChar = realloc(popChar, (j + 2) * sizeof(popChar));  //memory allocate to popChar
      popChar[j] = line[i];                                   //coping char by char
      j++;
      i++;
    }
    else {
      error(
          "Invalid input");  //maybe invalid population(NEGTIVE) or the state name broken by ':'
    }
  }
  popChar[j] = '\0';
  i++;
  state.population = (uint64_t)atoi(popChar);  //convert string to int, then to uint64_t
  free(popChar);                               //free memory

  while (line[i] != '\0') {
    //After the second ':',it must be the number or whitespace. No more letters or ':'
    if ((line[i] >= '0' && line[i] <= '9') || line[i] == ' ') {
      voteChar =
          realloc(voteChar, (k + 2) * sizeof(voteChar));  //memory allocate to voteChar
      voteChar[k] = line[i];
      k++;
      i++;
    }
    else {
      error("Invalid input");  //maybe invalid electoralVotes(NEGTIVE) or ':' again
    }
  }
  voteChar[k] = '\0';
  state.electoralVotes =
      (unsigned int)atoi(voteChar);  //convert string to int, then to unsigned int
  free(voteChar);                    //free memory

  return state;
}

/*ALL three functions below take three parameters:
 * stateData (which is a pointer to a arrary of state_t)
 * voteCounts(a pointer to a array of uint64_t stored the number of votes for candidateA))
 * naStates (which is the number of states)
 */

/* if Candidate A receives striclty more than 50% of the votes in that State, the he
 * receives ALL electoralvotes
*/
unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  unsigned int candiA = 0;
  for (size_t i = 0; i < nStates; i++) {
    uint64_t voteNeg =
        (stateData->population) - *voteCounts;  //the number of negative votes

    if (*voteCounts > voteNeg) {  //postive more than negtive
      candiA += (stateData->electoralVotes);
    }
    //go to the next
    stateData++;
    voteCounts++;
  }
  return candiA;
}

/*Decide which states need conducting recount*/
void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  for (size_t i = 0; i < nStates; i++) {
    float ratio = *voteCounts / (float)(stateData->population);
    if (ratio >= 0.495 && ratio <= 0.505) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData->name,
             ratio * 100);
    }
    //go to the next
    stateData++;
    voteCounts++;
  }
}

/*Find out in which state Candidate A won the largest percentage of the vote*/
void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  float largestRatio = 0;
  char * largestState;
  for (size_t i = 0; i < nStates; i++) {
    float winRatio = *voteCounts / (float)(stateData->population);
    if (winRatio > largestRatio) {
      largestRatio = winRatio;
      largestState = stateData->name;
    }
    //go to the next
    stateData++;
    voteCounts++;
  }
  printf(
      "Candidate A won %s with %.2f%% of the vote\n", largestState, largestRatio * 100);
}
