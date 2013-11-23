import patterns.command
import multiprocessing

from comm.messages import Messages
from comm.valueObjects import *
from concrete.model import RunningStateProxy, StaticStateProxy
#noinspection PyUnresolvedReferences
from libs import Sequencing

##
# Takes a list if \ref SequenceVO objects, and constructs a matrix of their scored pairwise comparisons.  This relies on
# the pyd as well.  It gets its settings from the \ref Model.  The pairwise comparisons occur in multiple processes, but
# is still blocking system wide until they are complete.  It queries the system for the number of CPU's, and uses this
# to determine the number of processes to run.
#
# @see patterns.command.SimpleCommand
# @see comm.valueObjects.SequenceVO
# @see core.Model
##
class CreateScoreMatrixCommand( patterns.command.SimpleCommand ) :
    def execute( self, notification ) :
        proxy = self.facade.retrieveProxy( RunningStateProxy.NAME )
        settings = proxy.getData()[ PairwiseSelectorVO.VONAME ]
        matrix = proxy.getData()[ MatrixFileVO.VONAME ].matrix
        sequences = proxy.getData()[ SequenceListVO.VONAME ].sequences

        if sequences is None :
            return

        if settings.analysisBoxValue == 'Affine':
            try :
                openGap = int( settings.openGapValue )
            except ValueError :
                openGap = StaticStateProxy.DEFAULT_OPEN_PENALTY

            try :
                extendGap = int( settings.extendedGapValue )
            except ValueError :
                extendGap = StaticStateProxy.DEFAULT_EXT_PENALTY
            items = self.buildAffineMSATasks( openGap, extendGap, matrix, sequences)
        else :
            try :
                gapPenalty = int( settings.gapPenaltyValue )
            except ValueError :
                gapPenalty = StaticStateProxy.DEFAULT_GAP_PENALTY

            if settings.analysisBoxValue == 'Global':
                useGlobal = 1
            else :
                useGlobal = 0
            items = self.buildLinearMSATasks( useGlobal, gapPenalty, matrix, sequences )

        results = self.runProcesses( items )
        smrvo = ScoreMatrixResultVO()
        smrvo.result = self.convertToMatrix( results, len( sequences ) )
        smrvo.names = []
        for seq in sequences :
            smrvo.names.append( seq.name )

        proxy.setData( smrvo )
        self.sendNotification( Messages.UPDATE_STATUS_TEXT, 'Score matrix successfully constructed.' )
        self.sendNotification( Messages.SHOW_RESULTS, smrvo.result )
        self.sendNotification( Messages.BUILD_NEWICK_TREE )

    ##
    # Converts a single dimension, upper diagonal, matrix, into a two dimensional matrix by reflecting its values
    # across the diagonal.
    #
    # @param upper the list of values that represent the upper diagonal matrix.  This is a single list that simply
    # represents a 2 dimensional upper diagonal matrix.
    # @param length the length of the top row of the matrix, it is use to calculate position.
    ##
    #noinspection PyUnusedLocal
    def convertToMatrix( self, upper, length ) :
        # This will create a length by length matrix filled with zeros.
        k = 0
        result = [[0 for col in range(length)] for row in range(length)]
        for i in range( 0, length ) :
            for j in range( 0, length ) :
                if i == j or i < j :
                    result[i][j] = upper[k]
                    k += 1
                else :
                    result[i][j] = result[j][i]
        return result

    ##
    # A helper method for processing a pool of worker functions while keeping them in order.
    #
    # @param items a list of items to be run in multiple processes.
    ##
    def runProcesses( self, items ) :
        result = []
        try :
            NUM_PROCESSORS = multiprocessing.cpu_count()
        except NotImplementedError :
            # Need to dispatch a notification to show an info screen.
            message = 'Unable to multi-thread because due to cpu count erring out.'
            title = 'Asynchronous Processing Error'
            self.sendNotification( Messages.SHOW_INFO, ( title, message ) )
            NUM_PROCESSORS = 1

        print( 'Number of processors: ',NUM_PROCESSORS )
        
        pool = multiprocessing.Pool( NUM_PROCESSORS )
        processMap = pool.imap( doStarScore, items )

        for i in processMap:
            result.append( i )
        
        return result


    ##
    # Constructs the data lists to be passes aa parameters to the worker methods in the process pool.  This one deals
    # specifically with the needs of the linear sequencing function.
    ##
    def buildLinearMSATasks( self, useGlobal, gapPenalty, matrix, sequences ) :
        items = []
        for i in range( 0, len( sequences ) ) :
            for j in range( i, len( sequences ) ) :
                items.append( ( doLinearPairwise, ( useGlobal, gapPenalty, matrix, sequences[i].seq, sequences[j].seq ) ) )
        return items

    ##
    # Constructs the data lists to be passes aa parameters to the worker methods in the process pool.  This one deals
    # specifically with the needs of the affine sequencing function.
    ##
    def buildAffineMSATasks( self, openGap, extendGap, matrix, sequences ) :
        items = []
        for i in range( 0, len( sequences ) ) :
            for j in range( i, len( sequences ) ) :
                items.append( ( doAffinePairwise, ( openGap, extendGap, matrix, sequences[i].seq, sequences[j].seq ) ) )
        return items

##
# calls the actual worker method defined by the state specific task pool creation methods.  This has to be a the main
# level because of limitations with Python.  On windows systems, processes can not be created in class methods.  Breaks
# the task list into the function and parameters to pass to doScore.
##
def doStarScore( args ) :
    return doScore( *args )

##
# Another helper function that calls the method passed to it, and unzips the parameter list to forward along.
#
# @param method the actual worker method to get the score from the sequence strings.
# @args the parameters to pass to the worker method.
##
def doScore( method, args ) :
    result = method( *args )
    return result

##
# A wrapper function for the linearSequence api provided through the c++ lib file.  This one is for linear sequencing.
##
def doLinearPairwise( useGlobal, gapPenalty, matrix, sequenceOne, sequenceTwo ) :
    # elements 0 and 1 of the return value of the linear sequence are the strings ith gaps inserted.
    score = Sequencing.linearSequence( useGlobal, gapPenalty, matrix, sequenceOne, sequenceTwo )[ 2 ]
    return score

##
# A wrapper function for the linearSequence api provided through the c++ lib file.  This one is for affine sequencing.
##
def doAffinePairwise( openGap, extendGap, matrix, sequenceOne, sequenceTwo ) :
    # elements 0 and 1 of the return value of the affine sequence are the strings ith gaps inserted.
    score = Sequencing.affineSequence( 1, openGap, extendGap, matrix, sequenceOne, sequenceTwo )[ 2 ]
    return score