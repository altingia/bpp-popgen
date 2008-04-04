//
// File GeneMapperCsvExport.cpp
// Authors : Sylvain Gaillard
// Last modification : April 2, 2008
//

/*
   Copyright or © or Copr. CNRS, (April 2, 2008)

   This software is a computer program whose purpose is to provide classes
   for population genetics analysis.

   This software is governed by the CeCILL  license under French law and
   abiding by the rules of distribution of free software.  You can  use, 
   modify and/ or redistribute the software under the terms of the CeCILL
   license as circulated by CEA, CNRS and INRIA at the following URL
   "http://www.cecill.info". 

   As a counterpart to the access to the source code and  rights to copy,
   modify and redistribute granted by the license, users are provided only
   with a limited warranty  and the software's author,  the holder of the
   economic rights,  and the successive licensors  have only  limited
   liability. 

   In this respect, the user's attention is drawn to the risks associated
   with loading,  using,  modifying and/or developing or reproducing the
   software by the user in light of its specific status of free software,
   that may mean  that it is complicated to manipulate,  and  that  also
   therefore means  that it is reserved for developers  and  experienced
   professionals having in-depth computer knowledge. Users are therefore
   encouraged to load and test the software's suitability as regards their
   requirements in conditions enabling the security of their systems and/or 
   data to be ensured and,  more generally, to use and operate it in the 
   same conditions as regards security. 

   The fact that you are presently reading this means that you have had
   knowledge of the CeCILL license and that you accept its terms.
   */

#include "GeneMapperCsvExport.h"

using namespace bpp;

GeneMapperCsvExport::GeneMapperCsvExport() {}

GeneMapperCsvExport::~GeneMapperCsvExport() {}

const string GeneMapperCsvExport::getFormatName()
{
  return "GeneMapper® cvs export";
}

const string GeneMapperCsvExport::getFormatDescription()
{
  return "GeneMapper® is a flexible genotyping software package that provides DNA sizing and quality allele calls for all Applied Biosystems electrophoresis-based genotyping systems.";
}

void GeneMapperCsvExport::read(istream & is, DataSet & data_set) throw (Exception)
{
  if (!is)
    throw IOException("GeneMapperCsvExport::read: fail to open stream.");
  bool debug = true;
  
  if (debug)
    cerr << "--- In GeneMapperCsvExport ---" << endl;

  /*
   * Feed a DataTable with the data
   */

  // Strange that's not working
  DataTable dt = * DataTable::read(is, "\t", true, -1);

  /*
  // So I do it by myself
  // Get the number of columns
  string line = FileTools::getNextLine(is);
  line = TextTools::removeLastNewLines(line); //Cleaning for garbage if file came from Micro$
  StringTokenizer st(line, "\t", true);
  // Create the DataTable according to the number of columns
  DataTable dt(st.numberOfRemainingTokens());
  // Set the columns' names
  vector<string> row1(st.getTokens().begin(), st.getTokens().end());
  dt.setColumnNames(row1);
  //Feed the DataTable with remaining rows
  while (!is.eof()) {
    line = FileTools::getNextLine(is);
    line = TextTools::removeLastNewLines(line);
    if (TextTools::isEmpty(line))
      continue;
    StringTokenizer st (line, "\t", true);
    vector<string> row2(st.getTokens().begin(), st.getTokens().end());
    dt.addRow(row2);
  }
  */

  /*
   * Fixe the individuals' name if there is duplicate in the file
   */
  vector<string> ind_names;
  vector<string> markers;
  try {
    ind_names = dt.getColumn("Sample Name");
    markers = dt.getColumn("Marker");
  }
  catch (Exception &e) {
    throw e;
  }
  map<string, int> indname_marker;
  for (unsigned int i = 0 ; i < dt.getNumberOfRows() ; i++) {
    string test_lab = dt(i, "Sample Name") + dt(i, "Marker");
    if (indname_marker.find(test_lab) != indname_marker.end()) {
      string new_lab = dt(i, "Sample Name") + "_" + TextTools::toString(indname_marker[test_lab] + 1);
      dt (i, "Sample Name") = new_lab;
    }
    indname_marker[test_lab]++;
  }
  ind_names = dt.getColumn("Sample Name");

  map<string, unsigned int> ind_count = VectorTools::countValues(ind_names);
  ind_names = VectorTools::unique(ind_names);
  markers= VectorTools::unique(markers);
  unsigned int loc_nbr = markers.size();

  if (debug) {
    cerr << "DataTable R x C : " << dt.getNumberOfRows() << " x " << dt.getNumberOfColumns() << endl;
    cerr << "Sample Name nbr : " << ind_names.size() << endl;
    cerr << "Marker nbr      : " << loc_nbr << endl;
    //for (unsigned int i = 0 ; i < ind_names.size() ; i++) {
    //  cerr << ind_names[i] << "[" << ind_count[ind_names[i]] << "] ";
    //}
    //cerr << endl;

    //for (unsigned int i = 0 ; i < dt.getNumberOfRows() ; i++) {
    //  cerr << dt.getRow(i).size() << endl;
    //}
  }

  /*
   * Loci number
   */
  data_set.initAnalyzedLoci(loc_nbr);

  /*
   * Group of individuals
   */
  data_set.addEmptyGroup(0);
  for (unsigned int i = 0 ; i < ind_names.size() ; i++) {
    Individual ind(ind_names[i]);
    data_set.addIndividualToGroup(data_set.getGroupPosition(0), ind);
  }

  /*
   * Loci data
   */
  AnalyzedLoci al(markers.size());
  vector<string> col_names = dt.getColumnNames();
  vector<unsigned int> alleles_cols;
  for (unsigned int i = 0 ; i < col_names.size() ; i++)
    if (TextTools::count(col_names[i], "Allele "))
      alleles_cols.push_back(i);
  vector<vector <unsigned int> > alleles_pos;
  for (unsigned int i = 0 ; i < markers.size() ; i++) {
    al.setLocusInfo(i, LocusInfo(markers[i], LocusInfo::UNKNOWN));
    vector<unsigned int> v = VectorTools::whichAll(dt.getColumn("Marker"), markers[i]);
    alleles_pos.push_back(v);
    if (debug)
      cerr << "marker " << markers[i] << " : " << v.size() << endl;
  }
  for (unsigned int i = 0 ; i < alleles_cols.size() ; i++) {
    for (unsigned int j = 0 ; j < markers.size() ; j++) {
      vector<string> m_allele;
      for (unsigned int k = 0 ; k < alleles_pos[j].size() ; k++) {
        if (dt(alleles_pos[j][k],alleles_cols[i]) != string(""))
          m_allele.push_back(dt(alleles_pos[j][k],alleles_cols[i]));
      }
      m_allele = VectorTools::unique(m_allele);
      //if (debug) {
      //  cerr << markers[j] << "\t" << m_allele.size() << "\t";
      //  VectorTools::print(m_allele, cerr);
      //}
      if (m_allele.size() > 0)
        al.addAlleleInfoByLocusName(markers[j], BasicAlleleInfo(m_allele[0]));
    }
  }
  data_set.setAnalyzedLoci(al);

  /*
   * Individuals informations
   */
  unsigned int ind_col_index = VectorTools::which(dt.getColumnNames(), string("Sample Name"));
  unsigned int mark_col_index = VectorTools::which(dt.getColumnNames(), string("Marker"));
  for (unsigned int i = 0 ; i < dt.getNumberOfRows() ; i++) {
    vector<unsigned int> alleles;
    for (unsigned int j = 0 ; j < alleles_cols.size() ; j++) {
      if (!TextTools::isEmpty(dt(i,alleles_cols[j]))) {
        //cerr << dt(i, mark_col_index) << " " << (data_set.getLocusInfoByName(dt(i, mark_col_index)))->getName() << " " << (data_set.getLocusInfoByName(dt(i,mark_col_index)))->getNumberOfAlleles() << endl;
        unsigned int num = (data_set.getLocusInfoByName(dt(i, mark_col_index)))->getAlleleInfoKey(dt(i,alleles_cols[j]));
        alleles.push_back(num);
      }
    }
    alleles = VectorTools::unique(alleles);
    MultiAlleleMonolocusGenotype ma(alleles);
    cerr << dt(i, ind_col_index) << " " << dt(i, mark_col_index) << " : ";
    VectorTools::print(alleles, cerr);
    if (!data_set.getIndividualByIdFromGroup(0,dt(i, ind_col_index))->hasGenotype())
      data_set.initIndividualGenotypeInGroup(0, data_set.getIndividualPositionInGroup(0,dt(i, ind_col_index)));
    if (alleles.size())
      data_set.setIndividualMonolocusGenotypeInGroup(0, data_set.getIndividualPositionInGroup(0, dt(i, ind_col_index)), data_set.getAnalyzedLoci()->getLocusInfoPosition(dt(i, mark_col_index)),ma);
  }

  /*
  // Groups
  for (unsigned int i = 0 ; i < grp_nbr ; i++) {
    data_set.addEmptyGroup(i);
    // Group name ... Now used khalid
    temp = FileTools::getNextLine(is);
    data_set.setGroupName(i, temp);

    // Number of individuals
    unsigned int ind_nbr;
    temp = FileTools::getNextLine(is);
    stringstream tmp(temp);
    tmp >> ind_nbr;
    for (unsigned int j = 0 ; j < ind_nbr ; j++) {
      temp = FileTools::getNextLine(is);
      string ind_name(temp.begin(), temp.begin()+11);
      temp = string(temp.begin()+11, temp.end());
      data_set.addEmptyIndividualToGroup(i, TextTools::removeSurroundingWhiteSpaces(ind_name) + string("_") + TextTools::toString(i+1) + string("_") + TextTools::toString(j+1));
      data_set.initIndividualGenotypeInGroup(i, j);
      StringTokenizer alleles(temp, string(" "));
      //cout << alleles.numberOfRemainingTokens() << endl;
      for (unsigned int k = 0 ; k < loc_nbr ; k++) {
        string tmp_string = alleles.nextToken();
        vector<string> tmp_alleles;
        tmp_alleles.push_back(string(tmp_string.begin(), tmp_string.begin() + 3));
        tmp_alleles.push_back(string(tmp_string.begin() + 3, tmp_string.begin() + 6));
        if (tmp_alleles[0] != string("000") && tmp_alleles[1] != string("000"))
          data_set.setIndividualMonolocusGenotypeByAlleleIdInGroup(i, j, k, tmp_alleles);
      }
    }
  }
  */
  if (debug)
    cerr << "--- Out GeneMapperCsvExport ---" << endl;
}

void GeneMapperCsvExport::read(const string & path, DataSet & data_set) throw (Exception)
{
  AbstractIDataSet::read(path, data_set);
}

DataSet * GeneMapperCsvExport::read(istream & is) throw (Exception)
{
  return AbstractIDataSet::read(is);
}

DataSet * GeneMapperCsvExport::read(const string & path) throw (Exception) 
{
  return AbstractIDataSet::read(path);
}

