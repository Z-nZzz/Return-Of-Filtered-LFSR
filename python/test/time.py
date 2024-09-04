from Crypto.Cipher import AES
from Crypto.Util import Counter
import time

# Clé de 128 bits
key = b'Sixteen byte key'

# Compteur initial
nonce = b'00000000'

# Taille du keystream en octets
keystream_size = 1000000 * 1024

# Créer un objet AES en mode CTR
ctr = Counter.new(128, initial_value=int.from_bytes(nonce, byteorder='big'))
cipher = AES.new(key, AES.MODE_CTR, counter=ctr)

# Mesurer le temps de début
start_time = time.time()

# Générer le keystream
keystream = cipher.encrypt(b'\x00' * keystream_size)

# Mesurer le temps de fin
end_time = time.time()

# Calculer le temps écoulé
elapsed_time = end_time - start_time

# Afficher le temps écoulé
print(f"Temps nécessaire à la génération du keystream : {elapsed_time:.6f} secondes")
