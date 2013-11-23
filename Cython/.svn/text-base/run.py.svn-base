import Sequencing
distance_matrix = []
list1 = [3, 3, 3, 2]
list2 = [2, 5, 2, 2]
list3 = [3, 2, 4, 3]
list4 = [3, 5, 5, 4]
distance_matrix.append(list1)
distance_matrix.append(list2)
distance_matrix.append(list3)
distance_matrix.append(list4)
sequences = ["ACGTACGACT", "AGCATCAGC", "GACTAGCG", "GACTACGATCG"]
substitution_matrix = Sequencing.loadSubstitutionMatrix("BLOSUM62.txt")
sequences = Sequencing.alignMultipleSequences(distance_matrix, substitution_matrix, sequences)
print(sequences)