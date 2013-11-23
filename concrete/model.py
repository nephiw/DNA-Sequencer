import patterns.proxy

##
# TODO: Implement state saving.
# This will pickle the state of the application to be loaded at a later time.  This is a future feature that has been
# stubbed in.
#
# @see patterns.proxy.Proxy
##
class SaveStateProxy( patterns.proxy.Proxy ) :
    NAME = 'SaveStateProxy'

    def __init__(self):
        super().__init__( SaveStateProxy.NAME, [] )
        # here we need to define the steps of pickling the state.

##
# Stores the values provided by the user during the operation of the application.
#
# The running state of the application is stored a a map of value objects.  Value objects are retrievable by name.
#
# @see patterns.proxy.Proxy
# @see comm.valueObjects.SequenceVO
# @see comm.valueObjects.DataSelectorVO
# @see comm.valueObjects.PairwiseSelectorVO
# @see comm.valueObjects.FileReturnVO
# @see comm.valueObjects.MatrixFileVO
# @see comm.valueObjects.SequenceListVO
# @see comm.valueObjects.ScoreMatrixResultVO
##
class RunningStateProxy( patterns.proxy.Proxy ) :
    NAME = 'RunningStateProxy'

    def __init__(self):
        super().__init__( RunningStateProxy.NAME, [] )

    def setData( self, data ) :
        ##
        # Stores the data in a map of value objects for access later.
        ##
        if self.data is None :
            self.data = {}
        # Each time this is called it will add the Value Object to the data dictionary, this dictionary can be pickled
        # and unpickled for saving state later.
        if data is not None :
            self.data[data.VONAME] = data
        else :
            print('Unable to set data that is Null.')

##
# Provides access for default values within the application.  These values are stored here to provide easy access
# at code time, and are therefore "read only".
#
# @see patterns.proxy.Proxy
##
class StaticStateProxy( patterns.proxy.Proxy ) :
    NAME = 'StaticStateProxy'
    DEFAULT_GAP_PENALTY = -1
    DEFAULT_OPEN_PENALTY = -4
    DEFAULT_EXT_PENALTY = -1

    def setData( self, data ) :
        ##
        # This state will remain the same for the life of the application, it should never get set.
        ##
        pass

    def getData(self) :
        return dict( BLOSUM45='matrices/BLOSUM45.txt', BLOSUM50='matrices/BLOSUM50.txt',
                     BLOSUM62='matrices/BLOSUM62.txt', BLOSUM80='matrices/BLOSUM80.txt',
                     PAM30='matrices/PAM30.txt', PAM70='matrices/PAM70.txt' )

