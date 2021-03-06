#!/bin/env python
import sys
import csv

import apsw

from rdkit import Chem

def chembl(path, limit=None):
    '''Parse the ChEMBLdb CSV format and return the chembl_id, smiles fields'''

    with open(path, 'rt') as inputfile:
        reader = csv.reader(inputfile, delimiter='\t', skipinitialspace=True)
        next(reader) # skip header line
        
        counter = 0
        for chembl_id, smiles, inchi, inchi_key in reader:
            
            # skip problematic compounds
            if len(smiles) > 300: continue
            smiles = smiles.replace('=N#N','=[N+]=[N-]')
            smiles = smiles.replace('N#N=','[N-]=[N+]=')
            if not Chem.MolFromSmiles(smiles): continue
            
            yield chembl_id, smiles
            counter += 1
            if counter == limit:
                break

def createdb(chemicalite_path, chembl_path):
    '''Initialize a database schema and load the ChEMBLdb data'''

    connection = apsw.Connection('chembldb.sql')
    connection.enableloadextension(True)
    connection.loadextension(chemicalite_path)
    connection.enableloadextension(False)

    cursor = connection.cursor()
    
    cursor.execute("PRAGMA page_size=4096")

    cursor.execute("CREATE TABLE chembl(id INTEGER PRIMARY KEY, "
                   "chembl_id TEXT, smiles TEXT, molecule MOL)")

    cursor.execute("SELECT create_molecule_rdtree('chembl', 'molecule')")

    cursor.execute("BEGIN")
    
    for chembl_id, smiles in chembl(chembl_path):
        cursor.execute("INSERT INTO chembl(chembl_id, smiles, molecule) "
                       "VALUES(?, ?, mol(?))", (chembl_id, smiles, smiles))

    cursor.execute("COMMIT")
    
if __name__=="__main__":
    if len(sys.argv) == 3:
        createdb(*sys.argv[1:3])
    else:
        print ('Usage: {0} <path to libchemicalite.so> '
               '<path to chembl_15_chemreps.txt>').format(sys.argv[0])
