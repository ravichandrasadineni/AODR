rsync -avz /home/ravichandrasadineni/Dropbox/AODR rsadineni@minix.cs.stonybrook.edu://home/stufs1/rsadineni/

ssh rsadineni@minix.cs.stonybrook.edu 'cd /home/stufs1/rsadineni/AODR/; make clean; make; /home/stufs1/rsadineni/cse533/deploy_app client server'
