from comm.messages import Messages
import patterns.command
from concrete import model
from concrete import mediators
from comm.valueObjects import *
from concrete.model import *
from libs import Sequencing
import subprocess
import patterns.command

##
# Handles the initialization of the \ref Model and \ref View by mapping the \ref Proxy and \ref Mediator instances respectively.
#
# @see patterns.command.SimpleCommand
##
class StartupCommand( patterns.command.SimpleCommand ) :
    def execute( self, notification ) :
        # This will need to be able to save the state of a command to rehydrate later.
        self.facade.registerProxy( model.SaveStateProxy() )
        self.facade.registerProxy( model.RunningStateProxy() )
        self.facade.registerProxy( model.StaticStateProxy() )

        gui = notification.body
        self.facade.registerMediator( mediators.MainWindowMediator( gui ) )
        self.facade.registerMediator( mediators.PairwiseSequenceMediator( gui.mainInterface.pairwiseSequenceTab ) )
        self.facade.registerMediator( mediators.DataSelectorMediator( gui.mainInterface.dataSelectTab ) )
        self.facade.registerMediator( mediators.ResultMediator( gui.mainInterface.resultsTab ) )
        # tkinter individual control based mediators.
        self.facade.registerMediator( mediators.ShowInfoMediator( None ) )
        self.facade.registerMediator( mediators.FileDialogMediator( None ) )

##
# Starts the sequence of events required to retrieve the values from the gui, to access the files, and call the
# sequencer algorithms.
#
# @see patterns.command.SimpleCommand
##
class StartAlignmentCommand( patterns.command.SimpleCommand ) :
    
    def execute( self, notification ) :
        self.sendNotification( Messages.STORE_CURRENT_STATE )
        # Each view will handle the notification in sequence and then this method will return to here.  This is not
        # asynchronous.
        # proxy will contain the values stored in all of the different view elements at this point.
        proxy = self.facade.retrieveProxy( RunningStateProxy.NAME )
        currentState = proxy.getData()
        data = currentState[ DataSelectorVO.VONAME ]
        singleSettings = currentState[ PairwiseSelectorVO.VONAME ]

        if singleSettings is not None :
            if singleSettings.matrixFileValue is not None and len( singleSettings.matrixFileValue ) > 0:
                self.sendNotification( Messages.GET_CUSTOM_SUB_MATRIX )
            elif singleSettings.matrixBoxValue is not None :
                self.sendNotification( Messages.GET_STORED_SUB_MATRIX )
            else :
                message = 'Error while loading substitution matrix, choice not found.'
                title = 'Invalid Input Error'
                self.sendNotification( Messages.SHOW_INFO, ( title, message ) )
                return

        if data is not None :
            if data.filePath is not None and data.filePath is not '':
                self.sendNotification( Messages.EXTRACT_SEQUENCES )
                self.sendNotification( Messages.UPDATE_STATUS_TEXT, 'Starting score matrix calculations.' )
                self.sendNotification( Messages.RUN_PAIRWISE_MATRIX )
            elif data.sequenceOne is not None and data.sequenceTwo is not None and len(data.sequenceOne.rstrip()) > 0 and len(data.sequenceTwo.rstrip()) > 0 :
                self.sendNotification( Messages.RUN_PAIRWISE_ONLY )
            else :
                message = 'Unable to run the pairwise because no data was set.'
                title = 'Data Not Set Error'
                self.sendNotification( Messages.SHOW_INFO, ( title, message ) )

##
# Saves the views states into the proxy.
#
# @see patterns.command.SimpleCommand
##
class SaveViewStateCommand( patterns.command.SimpleCommand ) :

    def execute( self, notification ) :
        proxy = self.facade.retrieveProxy( RunningStateProxy.NAME )
        proxy.setData( notification.getBody() )

##
# Reads in a txt file conformant to the fasta standard, and constructs an array of \ref SequenceVO objects for use in
# other commands.
#
# @see patterns.command.SimpleCommand
# @see comm.valueObjects.SequenceVO
##
class ParseFastaCommand( patterns.command.SimpleCommand ) :

    def execute( self, notification ) :
        proxy = self.facade.retrieveProxy( RunningStateProxy.NAME )
        fastaPath = proxy.getData()[ DataSelectorVO.VONAME ].filePath
        sequencesVo = SequenceListVO()
        sequencesVo.sequences = []
        seq = None
        self.sendNotification( Messages.UPDATE_STATUS_TEXT, 'Fasta file loaded, parsing it now.' )


        if fastaPath != None :
            try :
                fastaFile = open( fastaPath )

                for line in fastaFile :
                    cleanLine = str( line.rstrip() )
                    if line[0] == '>' :
                        if seq is not None :
                            sequencesVo.sequences.append( seq )
                        seq = SequenceVO()
                        seq.name = cleanLine[1:]
                        seq.seq = ''
                    elif seq is not None :
                        seq.seq += cleanLine

                sequencesVo.sequences.append( seq )
                proxy.setData( sequencesVo )
            except IOError :
                message = "Unable to open the file: %s please try another." % fastaPath
                title = 'IO Error'
                self.sendNotification( Messages.SHOW_INFO, ( title, message ) )
                sequencesVo.sequences = None
                proxy.setData( sequencesVo )
            else :
                fastaFile.close()

##
# Gets the matrix file location from the \ref Model and passes it to the pyd file to load in and parse.
#
# @see patterns.command.SimpleCommand
# @see core.Model
##
class ParseMatrixCommand( patterns.command.SimpleCommand ) :

    def execute( self, notification ) :
        proxy = self.facade.retrieveProxy( RunningStateProxy.NAME )
        state = proxy.getData()[PairwiseSelectorVO.VONAME]
        matrix = MatrixFileVO()

        if notification.getName() == Messages.GET_CUSTOM_SUB_MATRIX :
            matrixFile = state.matrixFileValue
        else :
            fileName = self.facade.retrieveProxy( StaticStateProxy.NAME )
            matrixFile = fileName.getData()[state.matrixBoxValue]
            
        if matrixFile is not None :
            try :
                matrix.matrix = Sequencing.loadSubstitutionMatrix( matrixFile )
                # TODO determine what other kinds of errors could be thrown by the matrix file creation.
            except IOError:
                if matrixFile != None :
                    message = "Unable to open the file: " + matrixFile + " please try another."
                else :
                    message = "Unable to open a null file."
                title = 'Data Not Set Error'
                self.sendNotification( Messages.SHOW_INFO, ( title, message ) )
            else :
                #TODO determine if there is clean up code required to be handled.
                pass
        proxy.setData( matrix )

##
# Compares two strings getting the settings from the \ref Model and returns the strings with gaps, as well as the score.
#
# @see patterns.command.SimpleCommand
# @see core.Model
##
class PairwiseCompareCommand( patterns.command.SimpleCommand ) :
    def execute( self, notification ) :
        proxy = self.facade.retrieveProxy( RunningStateProxy.NAME )
        settings = proxy.getData()[ PairwiseSelectorVO.VONAME ]
        data = proxy.getData()[ DataSelectorVO.VONAME ]
        matrix = proxy.getData()[ MatrixFileVO.VONAME ].matrix

        if settings.analysisBoxValue == 'Affine':
            try :
                openGap = int( settings.openGapValue )
            except ValueError :
                openGap = StaticStateProxy.DEFAULT_OPEN_PENALTY

            try :
                extendGap = int( settings.extendedGapValue )
            except ValueError :
                extendGap = StaticStateProxy.DEFAULT_EXT_PENALTY
                
            result = Sequencing.affineSequence( 1, openGap, extendGap, matrix, data.sequenceOne, data.sequenceTwo )
        else :
            try :
                gapPenalty = int( settings.gapPenaltyValue )
            except ValueError :
                gapPenalty = StaticStateProxy.DEFAULT_GAP_PENALTY

            if settings.analysisBoxValue == 'Global':
                useGlobal = 1
            else :
                useGlobal = 0

            result = Sequencing.linearSequence( useGlobal, gapPenalty, matrix, data.sequenceOne, data.sequenceTwo )
            
        self.sendNotification( Messages.SHOW_RESULTS, result )
        self.sendNotification( Messages.UPDATE_STATUS_TEXT, 'Sequences successfully aligned.' )

##
# Constructs a newick tree out of a score matrix, then notifies to show the results, as well as opening forester.jar
# to display the tree more graphically.
#
# @see patterns.command.SimpleCommand
# @see core.Model
##
class BuildNewickTreeCommand( patterns.command.SimpleCommand ) :

    def execute( self, notification ) :
        proxy = self.facade.retrieveProxy( RunningStateProxy.NAME )
        scoreMatrix = proxy.getData()[ ScoreMatrixResultVO.VONAME ]
        settings = proxy.getData()[ PairwiseSelectorVO.VONAME ]
        scores = scoreMatrix.result
        names = scoreMatrix.names
        
        result = Sequencing.constructNewickTree( scores, names )

        self.sendNotification( Messages.SHOW_RESULTS, result )
        if settings.useForester :
            self.sendNotification( Messages.SHOW_TREE_GRAPHICALLY, result )

##
# Takes the results from the body of a notification, creates a text file of those results, and opens this file with
# forester.jar This creates a new process for the opening of forester.jar so if there is an error that occurs in
# forester it will not crash this application.
#
# @see patterns.command.SimpleCommand
##
class OpenTreeInForester( patterns.command.SimpleCommand ) :
    def execute( self, notification ) :
        result = notification.getBody()

        file = open( 'generated_tree.txt', 'w' )
        file.write( result )
        file.close()

        args = ['java', '-jar', 'forester.jar','generated_tree.txt']
        subprocess.Popen(args)