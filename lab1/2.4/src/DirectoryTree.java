public class DirectoryTree {
    public static void main(String[] args) {
        // Definicja drzewa A
        String[][][] treeA = {
                { {"B", "D", "f1"}, {"C"}, {"D", "E"} }, // Poddrzewa dla A
                { {"f1"} }, // Pliki w B
                { {}, {}, {"f1"} } // Pliki w C i E
        };

        // Definicja drzewa X
        String[][][] treeX = {
                { {"Y", "Z", "f1"}, {"X", "Z", "f1"}, {"f1"} }, // Poddrzewa dla X
                { {"f1"}, {}, {} }, // Pliki w Y, Z
                { {}, {}, {"f1"} }  // Pliki w podkatalogach
        };
        System.out.println("Drzewo A:");
        printTree(treeA);

        System.out.println("\nDrzewo X:");
        printTree(treeX);
    }

    public static void printTree(String[][][] tree) {
        for (int i = 0; i < tree.length; i++) {
            for (int j = 0; j < tree[i].length; j++) {
                System.out.print("Katalog poziom " + i + ": ");
                for (int k = 0; k < tree[i][j].length; k++) {
                    System.out.print(tree[i][j][k] + " ");
                }
                System.out.println();
            }
        }
    }
}