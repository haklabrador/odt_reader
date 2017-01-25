import zipfile
import xml.etree.ElementTree as ET

def open(filename):
    return zipfile.ZipFile(filename)

def get_text(odtfile):
    # procitaj sadrzaj content.xml iz zip fajla
    contents = odtfile.read('content.xml')

    # izparsiraj XML
    root = ET.fromstring(contents)

    # izuci textualni sadrzaj iz text:p elemenata
    text = ''

    for el1 in root.findall('{urn:oasis:names:tc:opendocument:xmlns:office:1.0}body'):
        for el2 in el1.findall('{urn:oasis:names:tc:opendocument:xmlns:office:1.0}text'):
            for el3 in el2.iter():
                #print 'el3:', el3.text
                if el3.text:
                    text += el3.text + '\n'

    return text

if __name__ == '__main__':
    print get_text(open('doc1.odt')) # ispisi textualni sadrzaj odt fajla
    
