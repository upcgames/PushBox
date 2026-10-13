import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import copy_resources

SOURCE = 'void MusicaCongratulations(){ PlaySound(TEXT("Victory.wav"), NULL, SND_ASYNC); }'


class AudioResourcesTest(unittest.TestCase):
    def test_manifest_uses_exact_source_names(self):
        files, ending = copy_resources.audio_manifest(SOURCE, ['Victory.wav', 'Coin.wav'])
        self.assertEqual(files, ['Coin.wav', 'Victory.wav'])
        self.assertEqual(ending, 'Victory.wav')

    def test_case_drift_is_rejected_even_on_case_insensitive_hosts(self):
        with self.assertRaisesRegex(ValueError, 'asset spelling: victory.wav'):
            copy_resources.audio_manifest(SOURCE, ['victory.wav'])

    def test_missing_asset_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'missing: Victory.wav'):
            copy_resources.audio_manifest(SOURCE, [])

    def test_ambiguous_casing_is_rejected(self):
        with self.assertRaisesRegex(ValueError, 'Ambiguous'):
            copy_resources.audio_manifest(SOURCE, ['Victory.wav', 'victory.wav'])

    def test_conflicting_canonical_spellings_are_rejected(self):
        source = SOURCE + 'void Other(){ PlaySound(TEXT("victory.wav"), NULL, 0); }'
        with self.assertRaisesRegex(ValueError, 'missing: victory.wav'):
            copy_resources.audio_manifest(source, ['Victory.wav'])

    def test_generation_removes_stale_names_and_writes_shared_manifest(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            source, target, manifest = root / 'source', root / 'public', root / 'generated' / 'audioAssets.js'
            source.mkdir(); target.mkdir()
            (source / 'Source Code.cpp').write_text(SOURCE)
            (source / 'Victory.wav').write_bytes(b'audio')
            (target / 'victory.wav').write_bytes(b'stale')
            with patch.multiple(copy_resources, SOURCE_DIR=source, TARGET_DIR=target, MANIFEST=manifest):
                copy_resources.copy_resources()
            self.assertEqual([path.name for path in target.iterdir()], ['Victory.wav'])
            self.assertEqual((target / 'Victory.wav').read_bytes(), b'audio')
            self.assertIn('CONGRATULATIONS_MUSIC = "Victory.wav"', manifest.read_text())


if __name__ == '__main__':
    unittest.main()
