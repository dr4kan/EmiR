/*
###############################################################################
# Emir: EmiR: Evolutionary minimization forR                                  #
# Copyright (C) 2021-2024 Davide Pagano & Lorenzo Sostero                     #
#                                                                             #
# This program is free software: you can redistribute it and/or modify        #
# it under the terms of the GNU General Public License as published by        #
# the Free Software Foundation, either version 3 of the License, or           #
# any later version.                                                          #
#                                                                             #
# This program is distributed in the hope that it will be useful, but         #
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  #
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    #
# for more details: <https://www.gnu.org/licenses/>.                          #
###############################################################################
*/


#include <testthat.h>
#include <iostream>
#include "Base/Parameter.h"
#include "Base/SearchSpace.h"
#include "Base/Individual.h"
#include "Base/Utility.h"
#include "PS/PSPopulation.h"
#include "PS/PSConfig.h"
#include <Rcpp.h>
using namespace Rcpp;

///////////////////////////////////////////////////////////
bool equal_vec(std::vector<double>& v1, std::vector<double>& v2, double eps = 1.e-5) {
  if (v1.size() != v2.size()) return false;

  for (std::size_t i = 0; i < v1.size(); ++i) {
    if (fabs(v1[i] - v2[i]) >= eps) return false;
  }
  return true;
}

///////////////////////////////////////////////////////////
bool equal_vec(PSPopulation& p1, PSPopulation& p2, double eps = 1.e-5) {
  std::vector<std::vector<double> > v1 = p1.getPopulationPosition();
  std::vector<std::vector<double> > v2 = p2.getPopulationPosition();
  if (v1.size() != v2.size()) return false;

  for (std::size_t i = 0; i < v1.size(); ++i) {
    std::vector<double> vv1 = v1[i];
    std::vector<double> vv2 = v2[i];
    if (vv1.size() != vv2.size()) return false;

    for (std::size_t j = 0; j < vv1.size(); ++j) {
      if (fabs(vv1[j] - vv2[j]) >= eps) return false;
    }
  }
  return true;
}

///////////////////////////////////////////////////////////
void print(std::vector<double>& v) {
  for (std::size_t i = 0; i < v.size(); ++i) {
    Rcout << v[i] << " ";
  }
  Rcout << "\n";
}

///////////////////////////////////////////////////////////
void print(PSPopulation& pop) {
  Rcout << "--- Population ---\n";
  std::vector<std::vector<double> > v = pop.getPopulationPosition();
  for (std::size_t i = 0; i < v.size(); ++i) {
    std::vector<double> vv = v[i];
    for (std::size_t j = 0; j < vv.size(); ++j) {
      Rcout << vv[j] << " ";
    }
    Rcout << "\n";
  }
}

///////////////////////////////////////////////////////////
context("Test c++ classes") {
  Function f("rnorm");
  PSConfig ps_config;
  ps_config.setPopulationSize(5);

  Parameter p1("p1", -5.2, 5.2);
  Parameter p2("p2", -0.52, 1.2);
  Parameter p3("p3", 0.2, 5.2);
  Parameter p4("p4", 5.2, 15.2);

  Parameter p1_int("p1_int", -10.2, 5.2, true);
  Parameter p2_int("p2_int", -10  , 5.8, true);
  Parameter p3_int("p3_int", -10  , 5  , true);

  // Search space without seed
  SearchSpace sp_noseed(4);
  sp_noseed.setParameter(0, p1);
  sp_noseed.setParameter(1, p2);
  sp_noseed.setParameter(2, p3);
  sp_noseed.setParameter(3, p4);
  std::vector<double> p1_noseed = sp_noseed.getRandom();
  std::vector<double> p2_noseed = sp_noseed.getRandom();

  PSPopulation pop_noseed1(f);
  pop_noseed1.setConfig(ps_config);
  pop_noseed1.setSearchSpace(sp_noseed);
  pop_noseed1.init();

  sp_noseed = SearchSpace(4);
  sp_noseed.setParameter(0, p1);
  sp_noseed.setParameter(1, p2);
  sp_noseed.setParameter(2, p3);
  sp_noseed.setParameter(3, p4);

  PSPopulation pop_noseed2(f);
  pop_noseed2.setConfig(ps_config);
  pop_noseed2.setSearchSpace(sp_noseed);
  pop_noseed2.init();


  // Search space with mixed-integer parameters
  SearchSpace sp_mix_int(3);
  std::vector<std::vector<double> > p_mix_int(50);
  for (auto i = 0; i < 50; ++i) {
    p_mix_int[i] = sp_mix_int.getRandom();
  }

  std::vector<double> mag_v1 = {1., 2., 3.};
  std::vector<float> mag_v2  = {1., 2., 3.};
  std::vector<int> mag_v3    = { 1,  2, 3 };

  // Search space with seed
  SearchSpace sp_seed(4);
  sp_seed.setSeed(1234);
  sp_seed.setParameter(0, p1);
  sp_seed.setParameter(1, p2);
  sp_seed.setParameter(2, p3);
  sp_seed.setParameter(3, p4);
  std::vector<double> p1_seed = sp_seed.getRandom();

  sp_seed = SearchSpace(4);
  sp_seed.setSeed(1234);
  sp_seed.setParameter(0, p1);
  sp_seed.setParameter(1, p2);
  sp_seed.setParameter(2, p3);
  sp_seed.setParameter(3, p4);
  std::vector<double> p2_seed = sp_seed.getRandom();

  PSPopulation pop_seed1(f);
  pop_seed1.setConfig(ps_config);
  pop_seed1.setSearchSpace(sp_seed);
  pop_seed1.init();

  PSPopulation pop_seed2(f);
  pop_seed2.setConfig(ps_config);
  pop_seed2.setSearchSpace(sp_seed);
  pop_seed2.init();


  ////////////////////////////////////////////////////////
  ///                     TESTS                        ///
  ////////////////////////////////////////////////////////
  test_that("Magnitude function") {
    expect_true(fabs(Utility::magnitude(mag_v1) - 3.741657) < 1.e-4);
    expect_true(fabs(Utility::magnitude(mag_v2) - 3.741657) < 1.e-4);
    expect_true(fabs(Utility::magnitude(mag_v3) - 3.741657) < 1.e-4);
  }

  test_that("Parameter definition") {
    expect_true(p1.getMin() == -5.2);
    expect_true(p1.getMax() == 5.2);
    expect_true(p1.getName() == "p1");
    expect_true(fabs(p1.getWidth() - 10.4) < 1.e-5);

    expect_true(p4.getMin() == 5.2);
    expect_true(p4.getMax() == 15.2);
    expect_true(p4.getName() == "p4");
    expect_true(fabs(p4.getWidth() - 10.) < 1.e-5);
  }

  test_that("SearchSpace no seed: different random points") {
    expect_false(equal_vec(p1_noseed, p2_noseed));
  }

  test_that("SearchSpace with seed: same random points") {
    expect_true(equal_vec(p1_seed, p2_seed));
  }

  test_that("SearchSpace with mixed-interger parameters") {
    for (int i = 0; i < 50; ++i) {
      for (int j = 0; j < 3; ++j) {
        expect_true(p_mix_int[i][j] >= -10);
        expect_true(p_mix_int[i][j] <= 5);
      }
    }
  }

  test_that("PSPopulation with seed: same positions") {
    expect_true(equal_vec(pop_seed1, pop_seed2));
  }

  test_that("PSPopulation with no seed: different positions") {
    expect_false(equal_vec(pop_noseed1, pop_noseed2));
  }
}
