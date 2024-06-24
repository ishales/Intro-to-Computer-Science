//
//  main.cpp
//  ihproj4
//
//  Created by Isabelle Hales on 3/9/23.
//  Copyright © 2023 CS32. All rights reserved.
//
#include "UserDatabase.h"
#include "User.h"
#include "MovieDatabase.h"
#include "Movie.h"
#include "Recommender.h"
#include <iostream>
#include <string>

using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "/Users/isabellehales/Desktop/u.txt";
const string MOVIE_DATAFILE = "/Users/isabellehales/Desktop/movies.txt";

void findMatches(const Recommender& r, const MovieDatabase& md, const string& user_email,
  int num_recommendations) {
  // get up to ten movie recommendations for the user
  vector<MovieAndRank> recommendations = r.recommend_movies(user_email, num_recommendations);
      if (recommendations.empty())
         cout << "We found no movies to recommend :(.\n";
      else {
        for (int i = 0; i < recommendations.size(); i++) {
            const MovieAndRank& mr = recommendations[i];
            Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i+1 << ". " << m->get_title() << " (" << m->get_release_year() << ")\n Rating: "
            << m->get_rating() << "\n Compatibility Score: " << mr.compatibility_score << "\n" << "\n";
            }
        }
}

int main()
{
    UserDatabase udb;
    if (!udb.load(USER_DATAFILE))
    {
        cout << "Failed to load user data file " << USER_DATAFILE << "!" << endl;
        return 1;
    }

    MovieDatabase mdb;
    if (!mdb.load(MOVIE_DATAFILE))
    {
        cout << "Failed to load movie file " << MOVIE_DATAFILE << "!" << endl;
        return 1;
    }
    
    Recommender hi(udb, mdb);
    cout << "Enter user email address (or quit): ";
                string email;
                getline(cin, email);
    //hi.recommend_movies(email, 5);
    findMatches(hi, mdb, email, 5);
    
   
//    cout << "Enter user email address (or quit): ";
//            string email;
//            getline(cin, email);
//            if (email == "quit")
//                return 0;
//            User* u = udb.get_user_from_email(email);
//            cerr << u->get_full_name();
//    
//
//    cout << endl;
//
//    cout << "Enter movie id: ";
//        string id;
//        getline(cin, id);
//        if (id == "quit")
//            return 0;
//    Movie* m = mdb.get_movie_from_id(id);
//    cerr << m->get_title();

//    cout << "Enter movie dir: ";
//           string a;
//           getline(cin, a);
//    vector<Movie*> k = mdb.get_movies_with_director(a);
//    for(int i = 0; i < k.size(); i++){
//        cerr << k[i]->get_title() << endl;
//    }
    
//    cout << "Enter movie act: ";
//           string act;
//           getline(cin, act);
//    vector<Movie*> ats = mdb.get_movies_with_actor(act);
//    for(int bob = 0; bob < ats.size(); bob++){
//        cerr << ats[bob]->get_title() << endl;
//    }
    
//    cout << "Enter movie genre: ";
//           string gens;
//           getline(cin, gens);
//    vector<Movie*> ge = mdb.get_movies_with_genre(gens);
//    for(int go = 0; go < ge.size(); go++){
//        cerr << ge[go]->get_title() << endl;
//    }
    
//    for (;;)
//    {
//        cout << "Enter user email address (or quit): ";
//        string email;
//        getline(cin, email);
//        if (email == "quit")
//            return 0;
//        User* u = udb.get_user_from_email(email);
//        cerr << u->get_full_name();
//        if (u == nullptr)
//            cout << "No user in the database has that email address." << endl;
//        else
//            cout << "Found " << u->get_full_name() << endl;
//    }

}
