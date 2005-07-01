/*
 * File SequenceStatistics.h
 * Author : Eric Bazin <bazin@univ-montp2.fr>
 *          Sylvain Gaillard <yragael2001@yahoo.fr>
 * Last modification : Friday August 06 2004
 *
 * Copyright (C) 2004 Eric Bazin, Sylvain Gaillard and the
 *                    PopGenLib Development Core Team
 *
 * This file is part of PopGenLib.
 *
 * PopGenLib is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * PopGenLib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PopGenLib; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

//Secured inclusion of header's file
#ifndef _SEQUENCESTATISTICS_H_
#define _SEQUENCESTATISTICS_H_

//From the SeqLib library
#include <Seq/SiteIterator.h>
#include <Seq/SiteContainer.h>
#include <Seq/SymbolListTools.h>
#include <Seq/CodonAlphabet.h>
#include <Seq/GeneticCode.h>
#include <Seq/SiteContainerTools.h>

//From the PolyLib library
#include "PolymorphismSequenceContainer.h"

using namespace std;

class SequenceStatistics
{
	public:
		// Class destructor:
		~SequenceStatistics();

		/*******************************************************************************/
	public:

		/**
		 * @brief Compute the number of polymorphic site in an alignment
		 *
		 * Gaps are consider as mutations so if you want number of
		 * polymorphic site, you have to give a NonGapSiteIterator
		 *
		 * @param psc a PolymorphismSequenceContainer
		 * @param gapflag flag set by default to true if you don't want to
		 * take gap into account
		 */
		static unsigned int polymorphicSiteNumber(const PolymorphismSequenceContainer & psc, bool gapflag = true);


        /**
         *@brief Compute the number of parsimony informative sites in an alignment
         *@param a SiteIterator
         */
        static unsigned int parsimonyInformativeSiteNumber(SiteIterator & si);

        /**
         *@brief Compute the number of parsimony informative sites in an alignment
         *@param a SiteContainer, a boolean
         */
        static unsigned int parsimonyInformativeSiteNumber(const SiteContainer & v, bool gapflag =true);


		/**
		 * @brief Count the number of singleton nucleotides in an alignment.
		 *
		 * @param psc a PolymorphismSequenceContainer
		 * @param gapflag flag set by default to true if you don't want to
		 * take gap into account
		 */
		static unsigned int countSingleton(const PolymorphismSequenceContainer & psc, bool gapflag = true);

		/**
		 * @brief Count the total number of mutations in an alignment.
		 *
		 * This count is assumed to be under an infinite site model.
		 * @param psc a PolymorphismSequenceContainer
		 * @param gapflag flag set by default to true if you don't want to
		 * take gap into account
		 */
		static unsigned int totNumberMutations(const PolymorphismSequenceContainer & psc, bool gapflag = true);

                /**
		 * @brief Compute the number of triplet in an alignment
		 *
		 * Gaps are consider as mutation variant
		 *
		 * @param v a SiteIterator
		 */
                static unsigned int tripletNumber(SiteIterator & si);

                /**
		 * @brief Compute the number of triplet in an alignment
		 *
		 * @param v a SiteContainer
		 * @param gapflag set by default to true if you don't want to take gap into account
		 */
                static unsigned int tripletNumber(const SiteContainer & v, bool gapflag = true);


                /**
		 * @brief Compute the mean GC content in an alignment
		 *
		 * @param v a PolymorphismSequenceContainer
		 */
		static double gcContent(const PolymorphismSequenceContainer & psc);


		/*
		 * @brief Return the number of GC alleles and the total number of alleles at polymorphic sites only
		 *
		 * G vs C and A vs T polymorphism are not taken into account
		 * @param psc a PolymorphismSequenceContainer
		 * @param stopflag a boolean set by default to true if you don't want
		 * to take stop codons into account
		 */
		static vector<unsigned int> gcPolymorphism(const PolymorphismSequenceContainer & psc, bool stopflag = true);


		/**
		 * @brief Compute diversity estimator Theta of Watterson (1975)
		 *
		 * @param v a SiteContainer
		 */
		static double watterson75( const SiteContainer & v );

		/**
		 * @brief Compute diversity estimator Theta of Tajima (1983)
		 *
		 * @param v a SiteContainer
		 */
		static double tajima83( const SiteContainer & v );

		/**
		 * @brief Compute diversity estimator Theta of Watterson (1975)
		 *
		 * @f[
		 * \hat{\theta}_S=\frac{S}{a_1}
		 * @f]
		 * where @f$S@f$ is the number of polymorphic sites and @f$a_1@f$ is describe in SequenceStatistics::_getUsefullValues().
		 * @param psc a PolymorphismSequenceContainer
		 * @param gapflag flag set by default to true if you don't want to
		 * take gap into account
		 */
		static double watterson75( const PolymorphismSequenceContainer & psc, bool gapflag = true );

		/**
		 * @brief Compute diversity estimator Theta of Tajima (1983)
		 *
		 * @f[
		 * \hat{\theta}_\pi=1-\sum_{i=1}^{S}\sum_{j=1}^{4}\frac{k_{j,i}\times\left(k_{j,i}-1\right)}
		 * {n_i\times\left(n_i-1\right)} \qquad \textrm{with }k_{j,i}>0
		 * @f]
		 * where @f$k_{j,i}@f$ is the count of the j<sup>th</sup> state at the i<sup>th</sup> site,
		 * @f$n_i@f$ the number of nucleotides and @f$S@f$ the number of polymorphic sites.
		 * @param psc a PolymorphismSequenceContainer
		 * @param gapflag flag set by default to true if you don't want to
		 * take gap into account
		 */
		static double tajima83( const PolymorphismSequenceContainer & psc, bool gapflag = true );

		/**
		 * @brief Return the number of haplotype in the sample.
		 * Depaulis and Veuille (1998)
		 *
		 * @param psc a PolymorphismSequenceContainer
		 * @param gapflag flag set by default to true if you don't want to
		 * take gap into account
		 */
		static unsigned int DVK ( const PolymorphismSequenceContainer & psc, bool gapflag = true );

		/**
		 * @brief Return the haplotype diversity of a sample.
		 * Depaulis and Veuille (1998)
		 *
		 * @param psc a PolymorphismSequenceContainer
		 * @param gapflag flag set by default to true if you don't want to
		 * take gaps into account
		 */
		static double DVH ( const PolymorphismSequenceContainer & psc, bool gapflag = true );

		/**
		 * @brief Return the number of transitions.
		 *
		 * @param psc a PolymorphismSequenceContainer
		 */
		static unsigned int getNumberOfTransitions( const PolymorphismSequenceContainer & psc ); 
		
		/**
		 * @brief Return the number of transversions.
		 *
		 * @param psc a PolymorphismSequenceContainer
		 */
		static unsigned int getNumberOfTransversions( const PolymorphismSequenceContainer & psc );
		
		/**
		 * @brief Return the ratio of transitions/transversions.
		 *
		 * @param psc a PolymorphismSequenceContainer
		 */		
		 static double getTransitionsTransversionsRatio( const PolymorphismSequenceContainer & psc );

		/**
		 * @brief Compute the number of codon sites with stop codon
		 * @param si a SiteIterator
		 * @param alpha a CodonAlphabet
		 */
		static unsigned int stopCodonSiteNumber( SiteIterator & si, const CodonAlphabet & alpha );

		/**
		 * @brief Compute the number of codon sites with stop codon
		 * @param v a SiteContainer
		 * @param gapfalg a boolean set by default to true if you don't want to take gaps into account
		 */
		static unsigned int stopCodonSiteNumber(const SiteContainer & v, bool gapflag = true);



		/**
		 * @brief Compute the number of polymorphic codon with only one mutated site
		 * @param si a SiteIterator
		 * @param na a NucleicAlphabhet
		 * @param ca a CodonAlphabet
		 */
		static unsigned int monoSitePolymorphicCodonNumber( SiteIterator & si, const NucleicAlphabet & na, const CodonAlphabet & ca);


		/**
		 * @brief Compute the number of polymorphic codon with only one mutated site
		 * @param v a SiteContainer
		 * @param stopflag a boolean set by default to true if you don't want
		 * to take stop codon into account
		 * @param gapflag a boolean set by default to true if you don't want
		 * to take gaps into account
		 */
		static unsigned int monoSitePolymorphicCodonNumber(const SiteContainer & v, bool stopflag = true, bool gapflag = true);


		/**
		 * @brief Compute the number of synonymous polymorphic codon sites
		 * @param si a SiteIterator
		 * @param na a NucleicAlphabet
		 * @param ca a CodonAlphabet
		 */
		static unsigned int synonymousPolymorphicCodonNumber(SiteIterator & si, const NucleicAlphabet & na, const CodonAlphabet & ca);

		/**
		 * @brief Compute the number of synonymous polymorphic codon sites
		 * @param si a SiteIterator
		 * @param gc a GeneticCode
		 */
		static unsigned int synonymousPolymorphicCodonNumber(SiteIterator & si, const GeneticCode & gc);

		/**
		 * @brief Compute the number of synonymous polymorphic codon sites
		 *
		 * Gaps are automatically excluded
		 * @param v a SiteContainer
		 * @param stopflag a boolean set by default to true if you don't want to take stop codons into account
		 */
		static unsigned int synonymousPolymorphicCodonNumber(const SiteContainer & v, bool stopflag = true);

		/**
		 * @brief Compute the number of synonymous polymorphic codon sites
		 *
		 * Gaps are automatically excluded
		 * @param v a SiteContainer
		 * @param v a GeneticCode
		 * @param stopflag a boolean set by default to true if you don't want to take stop codons into account
		 */
		static unsigned int synonymousPolymorphicCodonNumber(const SiteContainer & v, const GeneticCode & gc,  bool stopflag = true);

		/**
		 * @brief Compute the synonymous nucleotide diversity, pi
		 * @param si a SiteIterator
		 * @param ca a CodonAlphabet
		 * @param gc a GeneticCode
		 * @param minchange a boolean set to false (see CodonSiteTools)
		 */
		static double piSynonymous(SiteIterator & si, const CodonAlphabet & ca, const GeneticCode & gc, bool minchange=false);

		/**
		 * @brief Compute the synonymous nucleotide diversity, pi
		 * @param si a SiteIterator
		 * @param gc a GeneticCode
		 * @param minchange a boolean set to false (see CodonSiteTools)
		 */
		static double piSynonymous(SiteIterator & si, const GeneticCode & gc, bool minchange=false);

		/**
		  * @brief Compute the synonymous nucleotide diversity, pi
		  *
		  * Gaps are automatically excluded
		  * @param v a SiteContainer
		  * @param stopfalg a boolean set by default to true if you don't want
		  * to take gaps into account
		  * @param minchange a boolean set to false (see CodonSiteTools)
		  */
		static double piSynonymous(const SiteContainer & v, bool stopflag = true, bool minchange=false);

		/**
		  * @brief Compute the synonymous nucleotide diversity, pi
		  *
		  * Gaps are automatically excluded
		  * @param v a SiteContainer
		  * @param gc a GeneticCode
		  * @param stopfalg a boolean set by default to true if you don't want
		  * to take gaps into account
		  * @param minchange a boolean set to false (see CodonSiteTools)
		  */
                static double piSynonymous(const SiteContainer & v, const GeneticCode & gc, bool stopflag = true, bool minchange=false);


		/**
		 * @brief Compute the non-synonymous nucleotide diversity, pi
		 * @param si a SiteIterator
		 * @param na a NucleicAlphabet
		 * @param ca a CodonAlphabet
		 * @param gc a GeneticCode
		 * @param minchange a boolean set to false (see CodonSiteTools)
		 */
		static double piNonSynonymous(SiteIterator & si, const NucleicAlphabet & na, const CodonAlphabet & ca, const GeneticCode & gc, bool minchange=false );

		/**
		 * @brief Compute the non-synonymous nucleotide diversity, pi
		 * @param si a SiteIterator
		 * @param gc a GeneticCode
		 * @param minchange a boolean set to false (see CodonSiteTools)
		 */
		static double piNonSynonymous(SiteIterator & si, const GeneticCode & gc, bool minchange=false );

		/**
		  * @breif Compute the non-synonymous nucleotide diversity, pi
		  *
		  * Gaps are automatically excluded
		  * @param v a SiteContainer
		  * @param stopfalg a boolean set by default to true if you don't want to take gaps into account
		  * @param minchange a boolean set to false (see CodonSiteTools)
		  */
		static double piNonSynonymous(const SiteContainer & v, bool stopflag = true, bool minchange=false);

		/**
		  * @brief Compute the non-synonymous nucleotide diversity, pi
		  *
		  * Gaps are automatically excluded
		  * @param v a SiteContainer
		  * @param gc a GeneticCode
		  * @param stopfalg a boolean set by default to true if you don't want
		  * to take gaps into account
		  * @param minchange a boolean set to false (see CodonSiteTools)
		  */
                static double piNonSynonymous(const SiteContainer & v, const GeneticCode & gc, bool stopflag = true, bool minchange=false);

		/**
		  * @brief Compute the mean number of synonymous site in an alignment
		  *
		  * A site is x% synonymous if x% of possible mutations are synonymous
		  * The transition/transversion can be taken into account (use the variable ratio)
		  * @param si a SiteIterator
		  * @param ca a CodonAlphabet
		  * @param gc a GeneticCode
		  * @param ratio a double set by default to 1 if you assume that
		  * transition equal transversion
		  * Return: pi non-synonymous
		  */
		static double meanSynonymousSitesNumber(SiteIterator & si, const CodonAlphabet & ca, const GeneticCode & gc, double ratio=1);

		/**
		  * @brief Compute the mean number of synonymous site in an alignment
		  *
		  * A site is x% synonymous if x% of possible mutations are synonymous
		  * The transition/transversion can be taken into account (use the variable ratio)
		  * @param si a SiteIterator
		  * @param gc a GeneticCode
		  * @param ratio a double set by default to 1 if you assume that
		  * transition equal transversion
		  * Return: pi non-synonymous
		  */
		static double meanSynonymousSitesNumber(SiteIterator & si, const GeneticCode & gc, double ratio=1) throw(Exception);

		/**
		  * @brief Compute the mean number of non-synonymous site in an alignment
		  *
		  * A site is x% synonymous if x% of possible mutations are synonymous
		  * The transition/transversion can be taken into account (use the variable ratio)
		  * @param si a SiteIterator
		  * @param gc a GeneticCode
		  * @param ratio a double set by default to 1 if you assume that
		  * transition equal transversion
		  * Return: pi non-synonymous
		  */
		static double meanNonSynonymousSitesNumber(SiteIterator & si, const GeneticCode & gc, double ratio=1) throw(Exception);

		/**
		  * @brief compute the mean number of synonymous site in an alignment
		  *
		  * A site is x% synonymous if x% of possible mutations are synonymous
		  * The transition/transversion can be taken into account (use the variable ratio)
		  * Gaps are automatically excluded
		  * @param v a SiteContainer
		  * @param ratio a double
		  * @param stopfalg a boolean set by dfault to true if you don't want
		  * to take stop codons into account
		  */
		static double meanSynonymousSitesNumber(const SiteContainer & v, double ratio=1, bool stopfalg = true);

		/**
		  * @brief compute the mean number of synonymous site in an alignment
		  *
		  * A site is x% synonymous if x% of possible mutations are synonymous
		  * The transition/transversion can be taken into account (use the variable ratio)
		  * Gaps are automatically excluded
		  * @param v a SiteContainer
		  * @param gc a GeneticCode
		  * @param ratio a double
		  * @param stopfalg a boolean set by default to true if you don't want
		  * to take stop codons into account
		  */
		static double meanSynonymousSitesNumber(const SiteContainer & v, const GeneticCode & gc, double ratio=1.0, bool stopflag=true) throw (Exception);

		/**
		  * @brief compute the mean number of non-synonymous site in an alignment
		  *
		  * A site is x% synonymous if x% of possible mutations are synonymous
		  * The transition/transversion can be taken into account (use the variable ratio)
		  * Gaps are automatically excluded
		  * @param v a SiteContainer
		  * @param gc a GeneticCode
		  * @param ratio a double
		  * @param stopfalg a boolean set by default to true if you don't want
		  * to take stop codons into account
		  */
		static double meanNonSynonymousSitesNumber(const SiteContainer & v, const GeneticCode & gc, double ratio=1.0, bool stopflag=true) throw (Exception);

		/**
		 * @brief Return the Tajima's D test (Tajima 1989).
		 *
		 * Calculation using the number of polymorphic (segregating) sites.
		 * @f[
		 * D=\frac{\hat{\theta}_\pi-\hat{\theta}_S}{\sqrt{\textrm{V}\left(\hat{\theta}_\pi-\hat{\theta}_S\right)}}
		 * =\frac{\hat{\theta}_\pi-\hat{\theta}_S}{\sqrt{e_1S+e_2S(S-1)}}
		 * @f]
		 * @param psc a PolymorphismSequenceContainer
		 * @param gapflag flag set by default to true if you don't want to
		 * take gap into account
		 */
		static double tajimaDSS(const PolymorphismSequenceContainer & psc, bool gapflag = true);

		/**
		 * @brief Return the Tajima's D test (Tajima 1989).
		 *
		 * Calculation using the total number of mutation.
		 * @f[
		 * D=\frac{\hat{\theta}_\pi-\frac{\eta}{a_1}}{\sqrt{e_1\eta+e_2\eta(\eta-1)}}
		 * @f]
		 * @param psc a PolymorphismSequenceContainer
		 * @param gapflag flag set by default to true if you don't want to
		 * take gap into account
		 */
		static double tajimaDTNM(const PolymorphismSequenceContainer & psc, bool gapflag = true);

		/**
		 * @brief Return the Fu and Li D test (1993).
		 *
		 * @param ingroup a PolymorphismSequenceContainer
		 * @param outgroup a PolymorphismSequenceContainer
		 */
		static double fuliD(const PolymorphismSequenceContainer & ingroup, const PolymorphismSequenceContainer & outgroup);

		/**
		 * @brief Return the Fu and Li D<sup>*</sup> test (1993).
		 *
		 * @param group a PolymorphismSequenceContainer
		 */
		static double fuliDstar(const PolymorphismSequenceContainer & group);

		/**
		 * @brief Return the Fu and Li F test (1993).
		 *
		 * @param ingroup a PolymorphismSequenceContainer
		 * @param outgroup a PolymorphismSequenceContainer
		 */
		static double fuliF(const PolymorphismSequenceContainer & ingroup, const PolymorphismSequenceContainer & outgroup);

		/**
		 * @brief Return the Fu and Li F<sup>*</sup> test (1993).
		 *
		 * @param group a PolymorphismSequenceContainer
		 */
		static double fuliFstar(const PolymorphismSequenceContainer & group);


	    /**
	     * @brief generate a special PolymorphismSequenceContainer for linkage disequilbrium analysis
	     *
         * Only polymorphic sites with 2 alleles are kept
         * The value 1 is assigned to the more frequent allele, and 0 to the less frequent
	     * @param psc a PolymorphismSequenceContainer
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
		static PolymorphismSequenceContainer * generateLDContainer(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0) throw (Exception);
	    /**
	     * @brief give the vector of the pairwise distances between site positions corresponding to a LD SequencePolymorphismContainer
	     *
	     * @param psc a PolymorphismSequenceContainer
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
		static Vdouble pairwiseDistances1(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0);


	    /**
	     * @brief give the vector of all mean pairwise distance between two sites to a LD SequencePolymorphismContainer
	     *
	     * pairwise distances are computed for each sequence separately, excluding gaps. Then the mean is taken over all the sequences
	     * @param psc a PolymorphismSequenceContainer
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
		static Vdouble pairwiseDistances2(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0);


	    /**
	     * @brief give the vector of all mean pairwise D value between two sites (Lewontin & Kojima 1964)
	     *
	     * @param psc a PolymorphismSequenceContainer
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
		static Vdouble pairwiseD(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give the vector of all mean pairwise D' value between two sites (Lewontin 1964)
	     *
	     * @param psc a PolymorphismSequenceContainer
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
		static Vdouble pairwiseDprime(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give the vector of all mean pairwise R� value between two sites (Hill&Robertson 1968)
	     *
	     * @param psc a PolymorphismSequenceContainer
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
		static Vdouble pairwiseR2(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0);


	    /**
	     * @brief give mean D over all pairwise comparisons
	     *
	     * @param psc a PolymorphismSequenceContainer
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
		static double meanD(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give mean D' over all pairwise comparisons
	     *
	     * @param psc a PolymorphismSequenceContainer
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
		static double meanDprime(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give mean R� over all pairwise comparisons
	     *
	     * @param psc a PolymorphismSequenceContainer
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
		static double meanR2(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give mean pairwise distances between sites / method 1: differences between sequences are not taken into account
	     *
	     * @param psc a PolymorphismSequenceContainer
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
		static double meanDistance1(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give mean pairwise distances between sites / method 2: differences between sequences are taken into account
	     *
	     * @param psc a PolymorphismSequenceContainer
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
		static double meanDistance2(const PolymorphismSequenceContainer & psc, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give the slope of the regression |D| = 1+a*distance
	     *
             * The slope is given in |D| per kb
             *
	     * @param psc a PolymorphismSequenceContainer
             * @param distance1 a boolean (true to use distance1, false to use distance2, false by default)
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
        static double originRegressionD(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0);


	    /**
	     * @brief give the slope of the regression |D'| = 1+a*distance
	     *
             * The slope is given in |D'| per kb
             *
	     * @param psc a PolymorphismSequenceContainer
             * @param distance1 a boolean (true to use distance1, false to use distance2, false by default)
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
        static double originRegressionDprime(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give the slope of the regression R� = 1+a*distance
	     *
             * The slope is given in R� per kb
             *
	     * @param psc a PolymorphismSequenceContainer
             * @param distance1 a boolean (true to use distance1, false to use distance2, false by default)
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
        static double originRegressionR2(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give the slope and the origin of the regression |D| = a*distance+b
	     *
             * The slope is given in |D| per kb
             *
	     * @param psc a PolymorphismSequenceContainer
             * @param distance1 a boolean (true to use distance1, false to use distance2, false by default)
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
       static Vdouble linearRegressionD(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give the slope and the origin of the regression |D'| = a*distance+b
	     *
             * The slope is given in |D'| per kb
             *
	     * @param psc a PolymorphismSequenceContainer
             * @param distance1 a boolean (true to use distance1, false to use distance2, false by default)
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
       static Vdouble linearRegressionDprime(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give the slope and the origin of the regression R� = a*distance+b
	     *
             * The slope is given in R� per kb
             *
	     * @param psc a PolymorphismSequenceContainer
             * @param distance1 a boolean (true to use distance1, false to use distance2, false by default)
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
        static Vdouble linearRegressionR2(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0);

	    /**
	     * @brief give the slope of the regression R� = 1/(1+a*distance)
	     *
             * To fit the theoretical prediction R� = 1/(1+4Nr)
             * The slope is given in R� per kb
             *
	     * @param psc a PolymorphismSequenceContainer
             * @param distance1 a boolean (true to use distance1, false to use distance2, false by default)
	     * @param keepsingleton a boolean (true by default, false to exclude singleton)
	     * @param freqmin a float (to exlude site with the lowest allele frequency less than the threshold given by freqmin, 0 by default)
	     */
        static double inverseRegressionR2(const PolymorphismSequenceContainer & psc, bool distance1=false, bool keepsingleton=true, double freqmin=0);



	private:
		/**
		 * @brief Count the number of mutation for a site.
		 */
		static unsigned int _getMutationNumber(const Site & site);

		/**
		 * @brief Count the number of singleton for a site.
		 */
		static unsigned int _getSingletonNumber(const Site & site);

		/**
		 * @brief Get usefull values for theta estimators.
		 *
		 * @return A map with 11 values. Keys are a1, a2, a1n, b1, b2, c1, c2, cn, dn, e1 and e2.
		 * The values are :
		 * @f[
		 * a_1=\sum_{i=1}^{n-1}\frac{1}{i} \qquad a_2=\sum_{i=1}^{n-1}\frac{1}{i^2}
		 * @f]
		 * @f[
		 * a_{1n}=\sum_{i=1}^{n}\frac{1}{i}
		 * @f]
		 * @f[
		 * b_1=\frac{n+1}{3(n-1)} \qquad b_2=\frac{2(n^2+n+3)}{9n(n-1)}
		 * @f]
		 * @f[
		 * c_1=b_1-\frac{1}{a_1} \qquad c_2=b_2-\frac{n+2}{a_1n}+\frac{a_2}{a_1^2}
		 * @f]
		 * @f[
		 * c_n=2\frac{na_1-2(n-1)}{(n-1)(n-2)}
		 * @f]
		 * @f[
		 * d_n=c_n+\frac{n-2}{(n-1)^2}+\frac{2}{n-1}\left(\frac{3}{2}-\frac{2a_{1n}-3}{n-2}-\frac{1}{n}\right)
		 * @f]
		 * @f[
		 * e_1=\frac{c_1}{a_1} \qquad e_2=\frac{c_2}{a_1^2+a_2}
		 * @f]
		 * where @f$n@f$ is the number of observed sequences.
		 */
		static map<string, double> _getUsefullValues(unsigned int n);

		/*******************************************************************************/
};
#endif // _SEQUENCESTATISTICS_H_
