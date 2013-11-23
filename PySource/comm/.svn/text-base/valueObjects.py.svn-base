__author__ = 'Nephi Wright'

##
# Holds the data for a single sequence.
##
class SequenceVO( object ) :
    VONAME = 'SequenceVo'
    name = None
    seq = None

##
# Stores the data passed to the application from the user for the data to be sequenced.
##
class DataSelectorVO( object ) :
    VONAME = 'DataSelectorVo'
    sequenceOne = None
    sequenceTwo = None
    filePath = None

##
# Stores the data passed to the application from the user for the settings of the sequencing algorithms.
##
class PairwiseSelectorVO( object ) :
    VONAME = 'PairwiseSelectorVo'
    openGapValue = None
    extendedGapValue = None
    gapPenaltyValue = None
    matrixFileValue = None
    matrixBoxValue = None
    analysisBoxValue = None
    useForester = None

##
# Stores the data to be used to open a browser window to get the path to a file.  Passes a reference to the
# entry field to be updated when the file is found.
#
# TODO Needs to be changed so that it doesn't contain view information.
class FileReturnVO( object ) :
    VONAME = 'FileReturnVo'
    path = None
    entry = None
    msg = None

##
# Stores the substitution matrix to be used in the sequence comparison algorithms.
##
class MatrixFileVO( object ) :
    VONAME = 'MatrixFileVO'
    matrix = None

##
# Stores the list of sequences to be used by the multiple sequence comparison algorithms.
##
class SequenceListVO( object ) :
    VONAME = 'SequenceListVo'
    sequences = None

##
# Stores the score matrix to be used by the multiple sequence comparison algorithms.
##
class ScoreMatrixResultVO( object ) :
    VONAME = 'ScoreMatrixResultVo'
    result = None
    names = None
    outerLoop = None
    innterLoop = None